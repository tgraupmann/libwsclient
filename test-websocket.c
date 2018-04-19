#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <json-c/json.h>

#include <wsclient/wsclient.h>

int onclose(wsclient *c) {
	fprintf(stderr, "onclose called: %d\n", c->sockfd);
	return 0;
}

int onerror(wsclient *c, wsclient_error *err) {
	fprintf(stderr, "onerror: (%d): %s\n", err->code, err->str);
	if(err->extra_code) {
		errno = err->extra_code;
		perror("recv");
	}
	return 0;
}

int onmessage(wsclient *c, wsclient_message *msg) {
	//fprintf(stderr, "onmessage: (%llu): %s\n", msg->payload_len, msg->payload);
	json_object * json = json_tokener_parse(msg->payload);
	printf("recieved object: %s\n", json_object_to_json_string(json));
	return 0;
}

int onopen(wsclient *c) {
	fprintf(stderr, "onopen called: %d\n", c->sockfd);
	json_object * msg = json_object_new_object();
	json_object_object_add(msg, "source", json_object_new_string("petchatz"));
	json_object_object_add(msg, "type", json_object_new_string("command"));
	json_object_object_add(msg, "name", json_object_new_string("register"));
	json_object_object_add(msg, "device_id", json_object_new_string("22222222"));

	printf("CJR sending: %s\n", json_object_to_json_string(msg));
	libwsclient_send(c, (char *) json_object_to_json_string(msg));
	return 0;
}

int main(int argc, char **argv) {
	//Initialize new wsclient * using specified URI
	wsclient *client = libwsclient_new("wss://192.168.1.105/?connection_type=petchatz&access_token=0.0.0");
	if(!client) {
		fprintf(stderr, "Unable to initialize new WS client.\n");
		exit(1);
	}
	//set callback functions for this client
	libwsclient_onopen(client, &onopen);
	libwsclient_onmessage(client, &onmessage);
	libwsclient_onerror(client, &onerror);
	libwsclient_onclose(client, &onclose);
	//bind helper UNIX socket to "test.sock"
	//One can then use netcat (nc) to send data to the websocket server end on behalf of the client, like so:
	// $> echo -n "some data that will be echoed by echo.websocket.org" | nc -U test.sock
	libwsclient_helper_socket(client, "test.sock");
	//starts run thread.
	libwsclient_run(client);

	while(1);
	//blocks until run thread for client is done.
	libwsclient_finish(client);
	return 0;
}

