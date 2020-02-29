#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "stdbool.h"

#include "utils.h"


//função para criar player
player* new_player(int tamanho) {
  player* player1 = (player*) malloc(sizeof(player));
  player1->HP = 0;
  player1->tamanho = tamanho;
  //inicializa o mapa
  player1->MAP = (char**) malloc(sizeof(char*)*tamanho);
  for(int i = 0; i < tamanho; i++) {
    player1->MAP[i] = (char*) malloc(sizeof(char)*tamanho);
  }
  //coloca o mapa com tudo a 0
  for(int i = 0; i < tamanho; i++) {
    for(int j = 0; j < tamanho; j++) {
      player1->MAP[i][j] = ' ';
    }
  }
  return player1;
}


//função para definir manual ou random
int getopt(int argc, char const *argv[]) {
  //opt a 1 -> manual, 2 -> random, default -> random
  int opt = 2;
  if(argc != 1 && strcmp(argv[1], "manual") == 0) {
    opt = 1;
  }
  return opt;
}


//função para printar o mapa
void printmap(char** map, int tamanho) {
  //printar o y
  printf("   ");
  for(int i = 0; i < tamanho; i++) {
    printf("%i ", i);
  }
  printf("\n");
  printf("   ");
  for(int i = 0; i < tamanho; i++) {
    printf("_ ");
  }

  //printar cada linha
  for(int i = 0; i < tamanho; i++) {
    //printar o x
    printf("\n%i |", i);
    for(int j = 0; j < tamanho; j++) {
      printf("%c ", map[j][i]);
    }
  }
  printf("\n");
}


//função que printa o mapa mas que so mostra agua e balas ja disparadas
void printmapenemy(char** map, int tamanho) {
  //printar o y
  printf("   ");
  for(int i = 0; i < tamanho; i++) {
    printf("%i ", i);
  }
  printf("\n");
  printf("   ");
  for(int i = 0; i < tamanho; i++) {
    printf("_ ");
  }

  //printar cada linha
  for(int i = 0; i < tamanho; i++) {
    //printar o x
    printf("\n%i |", i);
    for(int j = 0; j < tamanho; j++) {
      if(map[j][i] == '#') {
        printf("  ");
      }
      else {
        printf("%c ", map[j][i]);
      }
    }
  }
  printf("\n");
}


//função que coloca os barcos no mapa
player* definemap(player* player, int flag, int rbarcos) {
  //flag define se está em modo manual ou random
  //flag a 1 -> manual, 2 -> random

  //identificadores dos barcos e tamanhos




  //colocar barcos no caso de ser random
  if(flag == 2) {
    //numero de barcos a colocar

    for(int i = 0; i < rbarcos; i++) {
      int boat = rand()%5+1;
      int x = -1;
      int y = -1;
      int dir = -1;
      bool valid = false;
      //ciclo que verifica a possibilidade
      //de colocar o barco na posição
      while(x < 0 || y < 0 || valid == false) {
        //cordenadas do inicio do barco
        x = rand()%(player->tamanho);
        y = rand()%(player->tamanho);
        //direção 0 para cima, 1 para a direita...
        dir = rand()%4;
        valid = verify(player->MAP, x, y, dir, boat, player->tamanho);
      }
      player->MAP = addboat(player->MAP, x, y, dir, boat);
      player->HP += boat;
    }
  }
  //colocar barcos no caso de ser manual
  else {





  }
  return player;
}


//função para verificar se se pode colocar o barco
bool verify(char**map, int x, int y, int dir, int boat, int tamanho) {
  int addx = 0;
  int addy = 0;
  //switch que define os valores a adicionar ao x e ao y
  switch (dir) {
    case 0: {
      addx = 0;
      addy = -1;
      break;
    }
    case 1: {
      addx = 1;
      addy = 0;
      break;
    }
    case 2: {
      addx = 0;
      addy = 1;
      break;
    }
    case 3: {
      addx = -1;
      addy = 0;
      break;
    }
  }

  for(int i = 0; i < boat; i++) {
    if(x < 0 || y < 0|| x >= tamanho || y >= tamanho) {
      return false;
    }
    //printf("\tcordenadas atuais:\n");
    //printf("\tx = %i y = %i\n\tmap[%i][%i] = %c\n", x, y, x, y, map[x][y]);
    if(map[x][y] == '#') {
      return false;
    }
    x += addx;
    y += addy;
  }
  return true;
}


//função que adiciona barco ao mapa
char** addboat(char** map, int x, int y, int dir, int boat) {
  int addx = 0;
  int addy = 0;
  switch (dir) {
    case 0: {
      addx = 0;
      addy = -1;
      break;
    }
    case 1: {
      addx = 1;
      addy = 0;
      break;
    }
    case 2: {
      addx = 0;
      addy = 1;
      break;
    }
    case 3: {
      addx = -1;
      addy = 0;
      break;
    }
  }

  for (int i = 0; i < boat; i++) {
    map[x][y] = '#';
    x += addx;
    y += addy;
  }
  return map;
}


//função para disparar
player* shoot(player* shooter, player* shootee) {
  char wtv;
  int x = -1;
  int y = -1;
  printf("O seu mapa:\n");
  printmap(shooter->MAP, shooter->tamanho);
  printf("\n");
  printf("O mapa inimigo:\n");
  printmapenemy(shootee->MAP, shootee->tamanho);
  printf("Digite as cordenadas para disparar: ");
  scanf("%i %i", &x, &y);
  while(x < 0 || y < 0 || x >= shootee->tamanho || y >= shootee->tamanho) {
    printf("Cordenadas inseridas invalidas, digite outras: ");
    scanf("%i %i", &x, &y);
  }

  if((shootee->MAP[x][y] == 'X') || (shootee->MAP[x][y] == '0')) {
    printf("Já tinha disparado para ai, mais atenção na proxima!\n");
    scanf("%c", &wtv);
  }
  if(shootee->MAP[x][y] == '#') {
    printf("Acertou num barco!\n");
    shootee->MAP[x][y] = 'X';
    shootee->HP--;
    scanf("%c", &wtv);
  }
  if(shootee->MAP[x][y] == ' ') {
    printf("Não acertou!\n");
    shootee->MAP[x][y] = '0';
    scanf("%c", &wtv);
  }
  return shootee;
}
