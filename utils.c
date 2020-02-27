#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

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
      player1->MAP[i][j] = '0';
    }
  }
  return player1;
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
      printf("%c ", map[i][j]);
    }
  }
  printf("\n");
}

//função para definir manual ou random
int getopt(int argc, char const *argv[]) {
  //opt a 1 -> manual, 2 -> random, default -> random
  int opt = 2;
  if(argc != 1 && strcmp(argv[1], "manual") == 0) {
    opt = 1;
  }
  else opt = 2;
  return opt;
}

player* definemap(player* player, int flag) {
  //flag define se está em modo manual ou random
  //flag a 1 -> manual, 2 -> random

  //identificadores dos barcos e tamanhos
  int submarine = 1;        //*
  int destroyer = 2;        //**
  int cruiser = 3;          //***
  int batlleship = 4;       //****
  int aircraftCarrier = 5;  //*****

  //colocar barcos no caso de ser random
  if(flag == 2) {
    srand(time(0));
    int count = rand()%10+7;

    for(int i = 0; i < count; i++) {
      int boat = rand()%5+1;
      int x = -1;
      int y = -1;
      int dir = -1;
      bool verify = false;
      //ciclo que verifica a possibilidade
      //de colocar o barco na posição
      while(x < 0 && y < 0 && verify == false) {
        //cordenadas do inicio do barco
        x = rand()%(player->tamanho);
        y = rand()%(player->tamanho);
        //direção 0 para cima, 1 para a direita...
        dir = rand()%4;
        verify = verify(map, x, y, dir, tamanho);
      }
      map = addboat(map, x, y, dir, tamanho)
    }
  }
  //colocar barcos no caso de ser manual
  else {


  }


  return player;
}
