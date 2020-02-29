#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main() {
  srand(time(0));
  int i = rand();
  int j = rand();
  printf("%i %i\n", i, j);

  return 0;
}
