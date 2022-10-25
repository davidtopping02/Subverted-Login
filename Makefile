CC=gcc
CXX=g++
CPPFlag=-g $(shell root-config)
LDLIBS=$(shell root-config -lssl -lcrypto)

SRCS=login.cpp

login.o: login.cpp
	g++ -o login.o login.cpp authlib.h authlib.cpp -lssl -lcrypto