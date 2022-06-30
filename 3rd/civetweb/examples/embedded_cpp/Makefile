#!/bin/sh
all:
	g++ embedded_cpp.cpp ../../src/civetweb.c ../../src/CivetServer.cpp -DUSE_WEBSOCKET -I../../include -lpthread -ldl -std=c++11 -g -O0 -DNO_SSL -o ws_server -Wall
