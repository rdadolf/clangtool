#include <stdio.h>

int fib(int x) {
  if(x<2)
    return 1;
  else
    return fib(x-1) + fib(x-2);
}

int main(int argc, char **argv)
{
  int i;
  for(i=0; i<6; i++)
    printf("Hello Fibworld(%d): %d\n", i, fib(i));
  return 0;
}
