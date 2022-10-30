#include <stdio.h>
#include <string.h>
#include <unistd.h>

void center(void)
{
  char code[128];
  printf("Enter secret code !\nCode:   ");
  gets(code);			//take input
  printf("Entered Command center with code > %s .\n",code);
}

int main()
{
	char name[64];
	setvbuf(stdin, 0, 2, 0);		//no buffering in stdin and stdout
	setvbuf(stdout, 0, 2, 0);
	memset(name, 0, sizeof(name));		//fill name buffer with null bytes
	printf("What is your name?\nName: ");
	read(0, name, 64);			//read 64 bytes from stdin(0) to name
	printf("Hello "); printf(name);
	center();				//call center function
	return 0;
}