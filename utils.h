#ifndef UTILS_H
#define UTILS_H

typedef struct {
  int HP;
  char** MAP;
  int tamanho;
} player;

player* new_player(int tamanho);
int getopt(int argc, char const *argv[]);
void printmap(char** map, int tamanho);
player* definemap(player* player, int flag);
bool verify(char** map, int x, int y, int dir, int tamanho);
char** addboat(char** map, int x, int y, int dir, tamanho);

#endif
