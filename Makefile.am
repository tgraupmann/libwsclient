lib_LTLIBRARIES=libwsclient.la

library_includedir=$(includedir)/wsclient
library_include_HEADERS = wsclient.h config.h
AM_LDFLAGS = -lpthread
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = test-websocket

lbwsclient_la_CFLAGS = \
	-ggdb

libwsclient_la_SOURCES = wsclient.c base64.c sha1.c

test_websocket_CFLAGS = \
	-ggdb
	
test_websocket_LDFLAGS = \
	-lwsclient \
	-ljson-c
	
test_weboscket_SOURCE = \
	test-websocket.c

