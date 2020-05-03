#ifndef UTILS_H
#define UTILS_H

//struct que guarda os modelos dos barcos
typedef struct {
  char boat[5][5];
  int boatHP;
  char boatChar;
} boatInfo_t;

//struct que guarda o barco usado em jogo
typedef struct {
  char boat[5][5];
  int boatHP;
  char boatChar;
  int x, y;
} boat_t;

//struct da cell usada no mapa
typedef struct {
  boat_t* boat;
  char state;
} cell_t;

//struct do player
typedef struct {
  int HP;
  cell_t** MAP;
  int size;
} player_t;

//struct que tem o número de barcos a colocar no mapa
typedef struct {
  int nID[6];
  int nboats;
} boats_t;

//struct do jogo
typedef struct {
  player_t* player1;
  player_t* player2;
  boatInfo_t* boatsInfo;
  boats_t* boats;
} game_t;


game_t* initGame();
player_t* initPlayer(int size);
boatInfo_t* initBoatsInfo();
boat_t* initBoat(boatInfo_t* boatInfo, int dir);
game_t* setupGame(game_t* game);
boats_t* setupBoats(game_t*, int size, int opt);
player_t* setupMap(game_t* game, int playerid, int opt);
void printMap(player_t* player, int flag);
void printBoatTypes(boatInfo_t* boatsInfo);
bool verify(player_t* player, int x, int y, boat_t* boat);
player_t* addBoat(player_t* player, int x, int y, boat_t* boat);
player_t* shoot(player_t* shootee);
void freeGame(game_t* game);
#endif
