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
  printf("fib(5): %d\n", fib(5));
  return 0;
}
