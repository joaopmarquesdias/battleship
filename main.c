#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"

#include "utils.h"



int main(int argc, char const *argv[]) {
  srand(time(0));

  system("clear");

  //criar jogo
  game_t* game = initGame();

  //colocar barcos nos mapas
  game = setupGame(game);

  system("clear");

  //ciclo de jogo
  int rodada = 0;
  while((game->player1->HP > 0) && (game->player2->HP > 0)) {
    rodada++;
    //iniciar ronda
    {
      printf("Pressione enter para começar a rodada número %i\n",rodada);
      while(getchar() != '\n');

      system("clear");
    }
    //vez do player1
    {
      printf("Player 1 é a sua vez.\n");
      printf("Pressione Enter quando estiver pronto");
      while(getchar() != '\n');
      //print dos mapas
      printf("O seu mapa:\n");
      printMap(game->player1, 1);
      printf("O mapa inimigo:\n");
      printMap(game->player2, 2);

      game->player2 = shoot(game->player2);
      printf("Pressione enter para acabar a jogada");
      while(getchar() != '\n');
      system("clear");
    }
    //vez do player2
    {
      printf("Player 2 é a sua vez\n");
      printf("Pressione Enter quando estiver pronto");
      while(getchar() != '\n');
      //print dos mapas
      printf("O seu mapa:\n");
      printMap(game->player2, 1);
      printf("O mapa inimigo:\n");
      printMap(game->player1, 2);

      game->player1 = shoot(game->player1);
      printf("Pressione enter para acabar a jogada");
      while(getchar() != '\n');
      system("clear");
    }
    //printar estado de jogo
    {
      printf("Mapa do player 1:\n");
      printMap(game->player1, 2);
      printf("Mapa do player 2:\n");
      printMap(game->player2, 2);
    }
  }

  //acabar o jogo e printar o vencedor
  if(game->player1->HP == 0 && game->player2->HP == 0) {
    printf("Foi um empate!");
  }
  else {
    if(game->player1->HP > 0) {
      printf("Ganhou o player 1!\nParabéns!\n");
    }
    if(game->player2->HP > 0) {
      printf("Ganhou o player 2!\nParabéns!\n");
    }
  }
  printf("O jogo teve um total de %i rodadas\n", rodada);

  //libertar a memória do jogo
  freeGame(game);

  return 0;
}
