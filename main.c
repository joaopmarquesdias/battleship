#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"

#include "utils.h"

#define Name(name)  #name

int main(int argc, char const *argv[]) {

  //obter opção manual ou random
  //opt a 1 -> manual, 2 -> random, default -> random
  int opt = getopt(argc, argv);
  srand(time(0));
  //int tamanho = rand()%10+10;

  //criar players
  player* player1 = new_player(10);
  player* player2 = new_player(10);

  //prints teste
  //printmap(player1->MAP, player1->tamanho);
  //printf("\n");
  //printmap(player2->MAP, player2->tamanho);

  //numero de barcos a colocar em cada mapa no caso de ser random
  int rbarcos = rand()%10+7;
  //colocar os barcos nos mapas
  player1 = definemap(player1, opt, rbarcos);
  player2 = definemap(player2, opt, rbarcos);
  system("clear");

  //ciclo de jogo
  int rodada = 0;
  while((player1->HP > 0) && (player2->HP > 0)) {
    char wtv;
    rodada++;
    //iniciar ronda
    {
      printf("Pressione enter para começar a rodada numero %i\n",rodada);
      scanf("%c", &wtv);
      system("clear");
    }
    //vez do player1
    {
      printf("%s é a sua vez.\n", Name(player1));
      printf("Pressione Enter quando estiver pronto");
      scanf("%c", &wtv);
      while(wtv != '\n') {
        printf("Pressione Enter quando estiver pronto");
        scanf("%c", &wtv);
      }
      player2 = shoot(player1, player2);
      printf("Pressione enter para acabar a jogada");
      scanf("%c", &wtv);
      system("clear");
    }
    //vez do player2
    {
      printf("%s é a sua vez.\n", Name(player2));
      printf("Pressione Enter quando estiver pronto");
      scanf("%c", &wtv);
      while(wtv != '\n') {
        printf("Pressione Enter quando estiver pronto");
        scanf("%c", &wtv);
      }
      player1 = shoot(player2, player1);
      printf("Pressione enter para acabar a jogada");
      scanf("%c", &wtv);
      system("clear");
    }
    //printar estado de jogo
    {
      printf("Mapa do player 1:\n");
      printmapenemy(player1->MAP, player1->tamanho);
      printf("Mapa do player 2:\n");
      printmapenemy(player2->MAP, player2->tamanho);
    }
  }

  //acabar o jogo e printar o vencedor
  if(player1->HP > 0) {
    printf("Ganhou o player 1!\nParabéns!\n");
  }
  if(player2->HP > 0) {
    printf("Ganhou o player 2!\nParabéns!\n");
  }
  printf("O jogo teve um total de %i rodadas\n", rodada);
  return 0;
}
