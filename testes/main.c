#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main() {
  srand(time(0));
  int i = rand();
  printf("%i\n", i%10+10);

  return 0;
}
