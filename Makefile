CC=gcc
CXX=g++
CPPFlag=-g $(shell root-config) -Wall -Wextra -pedantic
LDLIBS=$(shell root-config -lssl -lcrypto)

SRCS=login.cpp

login.o: login.cpp
	g++ -o login.o login.cpp authlib.h authlib.cpp -lssl -lcrypto

clean:
	-@rm *.o *.out 2>/dev/null || true
