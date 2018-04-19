lib_LTLIBRARIES=libwsclient.la
libwsclient_la_SOURCES = wsclient.c base64.c sha1.c
library_includedir=$(includedir)/wsclient
library_include_HEADERS = wsclient.h config.h
AM_LDFLAGS = -lpthread
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = test-websocket

test_websocket_CFLAGS = \
	-DDEBUG \
	-ggdb
	
test_websocket_LDFLAGS = \
	-lwsclient \
	-ljson-c
	
test_weboscket_SOURCE = \
	test-websocket.c

