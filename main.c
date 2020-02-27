#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

#include "utils.h"

int main(int argc, char const *argv[]) {

  //obter opção manual ou random
  //opt a 1 -> manual, 2 -> random, default -> random
  //int opt = getopt(argc, argv);
  //criar players
  srand(time(0));
  int tamanho = rand()%10+10;

  player* player1 = new_player(tamanho);
  player* player2 = new_player(tamanho);

  //prints teste
  printmap(player1->MAP,player1->tamanho);
  printf("\n");
  printmap(player2->MAP,player2->tamanho);


  return 0;
}
