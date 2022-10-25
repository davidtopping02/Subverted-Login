CC=gcc
CXX=g++
CPPFlag=-g $(shell root-config) -Wall -Wextra -pedantic
LDLIBS=$(shell root-config -lssl -lcrypto)

SRCS=login.cpp

login.o: login.cpp
	$(CC) $(LDLIBS) $(CPPFlag) -o login.o login.cpp authlib.h authlib.cpp
clean:
	-@rm *.o *.out 2>/dev/null || true
