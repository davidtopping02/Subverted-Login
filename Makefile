CPP = g++
CPPFlag=-g -Wall -Wextra -pedantic
LDLIBS= -lssl -lcrypto

SRCS=login.cpp

login.o: login.cpp
	$(CPP) -o login.o login.cpp authlib.h authlib.cpp $(CPPFlag) $(LDLIBS)

login-subverted.o: login-subverted.cpp
	$(CPP) -o login-subverted.o login-subverted.cpp authlib.h authlib.cpp $(CPPFlag) $(LDLIBS)
	
clean:
	-@rm *.o *.out 2>/dev/null || true
