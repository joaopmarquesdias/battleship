#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "stdbool.h"

#include "utils.h"



//função para criar game
game_t* initGame() {
  int size = 20;
  printf("Qual o tamanho dos mapas?\n");
  printf("O tamanho deve ser entre 20 e 40.\n");
  while(1) {
    int result = scanf("%i", &size);
    while(getchar() != '\n');
    if(size < 20 || size > 40 || result < 1) {
      printf("Input inválido, tente novamente.");
      continue;
    }
    break;
  }
  game_t* game = (game_t*) malloc(sizeof(game_t));
  game->player1 = initPlayer(size);
  game->player2 = initPlayer(size);
  game->boatsInfo = initBoatsInfo();
  //boats não é initializado aqui, apenas declarado
  //a inicialização está em setupBoats
  game->boats = (boats_t*) malloc(sizeof(boats_t));
  return game;
}


//função para criar player
player_t* initPlayer(int size) {
  player_t* player = (player_t*) malloc(sizeof(player_t));
  player->HP = 0;
  player->size = size;
  //inicializa o mapa
  player->MAP = (cell_t**) malloc(sizeof(cell_t*)*size);
  for(int i = 0; i < size; i++) {
    player->MAP[i] = (cell_t*) malloc(sizeof(cell_t)*size);
  }

  //coloca o mapa sem barcos
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      player->MAP[i][j].boat = NULL;
      player->MAP[i][j].state = ' ';
    }
  }
  return player;
}


//função para criar boatsInfo
boatInfo_t* initBoatsInfo() {
  boatInfo_t* boatsInfo = (boatInfo_t*) malloc(6*sizeof(boatInfo_t));
  boatsInfo[1].boatHP = 3;
  boatsInfo[2].boatHP = 4;
  boatsInfo[3].boatHP = 5;
  boatsInfo[4].boatHP = 5;
  boatsInfo[5].boatHP = 5;

  boatsInfo[1].boatChar = 'A';
  boatsInfo[2].boatChar = 'B';
  boatsInfo[3].boatChar = 'C';
  boatsInfo[4].boatChar = 'D';
  boatsInfo[5].boatChar = 'E';

  //as inicializações das matrizes são feitas por esta ordem para se
  //conseguir perceber qual a forma padrão que aparece no mapa de jogo
  //inicialização do cruiser
  {
    boatsInfo[1].boat[0][4] = ' '; boatsInfo[1].boat[1][4] = ' '; boatsInfo[1].boat[2][4] = ' '; boatsInfo[1].boat[3][4] = ' '; boatsInfo[1].boat[4][4] = ' ';
    boatsInfo[1].boat[0][3] = ' '; boatsInfo[1].boat[1][3] = ' '; boatsInfo[1].boat[2][3] = ' '; boatsInfo[1].boat[3][3] = ' '; boatsInfo[1].boat[4][3] = ' ';
    boatsInfo[1].boat[0][2] = ' '; boatsInfo[1].boat[1][2] = '#'; boatsInfo[1].boat[2][2] = '#'; boatsInfo[1].boat[3][2] = '#'; boatsInfo[1].boat[4][2] = ' ';
    boatsInfo[1].boat[0][1] = ' '; boatsInfo[1].boat[1][1] = ' '; boatsInfo[1].boat[2][1] = ' '; boatsInfo[1].boat[3][1] = ' '; boatsInfo[1].boat[4][1] = ' ';
    boatsInfo[1].boat[0][0] = ' '; boatsInfo[1].boat[1][0] = ' '; boatsInfo[1].boat[2][0] = ' '; boatsInfo[1].boat[3][0] = ' '; boatsInfo[1].boat[4][0] = ' ';
  }
  //inicialização do battleship
  {
    boatsInfo[2].boat[0][4] = ' '; boatsInfo[2].boat[1][4] = ' '; boatsInfo[2].boat[2][4] = ' '; boatsInfo[2].boat[3][4] = ' '; boatsInfo[2].boat[4][4] = ' ';
    boatsInfo[2].boat[0][3] = ' '; boatsInfo[2].boat[1][3] = ' '; boatsInfo[2].boat[2][3] = ' '; boatsInfo[2].boat[3][3] = ' '; boatsInfo[2].boat[4][3] = ' ';
    boatsInfo[2].boat[0][2] = ' '; boatsInfo[2].boat[1][2] = '#'; boatsInfo[2].boat[2][2] = '#'; boatsInfo[2].boat[3][2] = '#'; boatsInfo[2].boat[4][2] = '#';
    boatsInfo[2].boat[0][1] = ' '; boatsInfo[2].boat[1][1] = ' '; boatsInfo[2].boat[2][1] = ' '; boatsInfo[2].boat[3][1] = ' '; boatsInfo[2].boat[4][1] = ' ';
    boatsInfo[2].boat[0][0] = ' '; boatsInfo[2].boat[1][0] = ' '; boatsInfo[2].boat[2][0] = ' '; boatsInfo[2].boat[3][0] = ' '; boatsInfo[2].boat[4][0] = ' ';
  }
  //inicialização do aircraftCarrier
  {
    boatsInfo[3].boat[0][4] = ' '; boatsInfo[3].boat[1][4] = ' '; boatsInfo[3].boat[2][4] = ' '; boatsInfo[3].boat[3][4] = ' '; boatsInfo[3].boat[4][4] = ' ';
    boatsInfo[3].boat[0][3] = ' '; boatsInfo[3].boat[1][3] = ' '; boatsInfo[3].boat[2][3] = ' '; boatsInfo[3].boat[3][3] = ' '; boatsInfo[3].boat[4][3] = ' ';
    boatsInfo[3].boat[0][2] = '#'; boatsInfo[3].boat[1][2] = '#'; boatsInfo[3].boat[2][2] = '#'; boatsInfo[3].boat[3][2] = '#'; boatsInfo[3].boat[4][2] = '#';
    boatsInfo[3].boat[0][1] = ' '; boatsInfo[3].boat[1][1] = ' '; boatsInfo[3].boat[2][1] = ' '; boatsInfo[3].boat[3][1] = ' '; boatsInfo[3].boat[4][1] = ' ';
    boatsInfo[3].boat[0][0] = ' '; boatsInfo[3].boat[1][0] = ' '; boatsInfo[3].boat[2][0] = ' '; boatsInfo[3].boat[3][0] = ' '; boatsInfo[3].boat[4][0] = ' ';
  }
  //inicialização do bomber
  {
    boatsInfo[4].boat[0][4] = ' '; boatsInfo[4].boat[1][4] = ' '; boatsInfo[4].boat[2][4] = ' '; boatsInfo[4].boat[3][4] = ' '; boatsInfo[4].boat[4][4] = ' ';
    boatsInfo[4].boat[0][3] = ' '; boatsInfo[4].boat[1][3] = ' '; boatsInfo[4].boat[2][3] = ' '; boatsInfo[4].boat[3][3] = ' '; boatsInfo[4].boat[4][3] = '#';
    boatsInfo[4].boat[0][2] = ' '; boatsInfo[4].boat[1][2] = '#'; boatsInfo[4].boat[2][2] = '#'; boatsInfo[4].boat[3][2] = '#'; boatsInfo[4].boat[4][2] = '#';
    boatsInfo[4].boat[0][1] = ' '; boatsInfo[4].boat[1][1] = ' '; boatsInfo[4].boat[2][1] = ' '; boatsInfo[4].boat[3][1] = ' '; boatsInfo[4].boat[4][1] = ' ';
    boatsInfo[4].boat[0][0] = ' '; boatsInfo[4].boat[1][0] = ' '; boatsInfo[4].boat[2][0] = ' '; boatsInfo[4].boat[3][0] = ' '; boatsInfo[4].boat[4][0] = ' ';
  }
  //inicialização do destroyer
  {
    boatsInfo[5].boat[0][4] = ' '; boatsInfo[5].boat[1][4] = ' '; boatsInfo[5].boat[2][4] = ' '; boatsInfo[5].boat[3][4] = ' '; boatsInfo[5].boat[4][4] = ' ';
    boatsInfo[5].boat[0][3] = ' '; boatsInfo[5].boat[1][3] = ' '; boatsInfo[5].boat[2][3] = '#'; boatsInfo[5].boat[3][3] = ' '; boatsInfo[5].boat[4][3] = ' ';
    boatsInfo[5].boat[0][2] = ' '; boatsInfo[5].boat[1][2] = '#'; boatsInfo[5].boat[2][2] = '#'; boatsInfo[5].boat[3][2] = '#'; boatsInfo[5].boat[4][2] = ' ';
    boatsInfo[5].boat[0][1] = ' '; boatsInfo[5].boat[1][1] = ' '; boatsInfo[5].boat[2][1] = '#'; boatsInfo[5].boat[3][1] = ' '; boatsInfo[5].boat[4][1] = ' ';
    boatsInfo[5].boat[0][0] = ' '; boatsInfo[5].boat[1][0] = ' '; boatsInfo[5].boat[2][0] = ' '; boatsInfo[5].boat[3][0] = ' '; boatsInfo[5].boat[4][0] = ' ';
  }

  return boatsInfo;
}


//função que cria um barco
boat_t* initBoat(boatInfo_t* boatInfo, int dir) {
  boat_t* boat = (boat_t*) malloc(sizeof(boat_t));

  //inicialmente o barco ainda nao está colocado por isso as
  //cordenadas do seu centro então a -1
  boat->x = -1;
  boat->y = -1;
  boat->boatHP = boatInfo->boatHP;
  boat->boatChar = boatInfo->boatChar;

  //tratar da rotação do barco
  if(dir == 0) {
    for(int i = 0; i < 5; i++) {
      for(int j = 0; j < 5; j++) {
        boat->boat[i][j] = boatInfo->boat[i][j];
      }
    }
  }

  if(dir == 1) {
    for(int i = 0, ii = 0; i < 5 && ii < 5; i++, ii++) {
      for(int j = 0, jj = 4; j < 5 && jj >-1; j++, jj--) {
        boat->boat[i][j] = boatInfo->boat[jj][ii];
      }
    }
  }

  if(dir == 2) {
    for(int i = 0, ii = 4; i < 5 && ii > -1; i++, ii--) {
      for(int j = 0, jj = 4; j < 5 && jj >-1; j++, jj--) {
        boat->boat[i][j] = boatInfo->boat[ii][jj];
      }
    }
  }

  if(dir == 3) {
    for(int i = 0, ii = 4; i < 5 && ii > -1; i++, ii--) {
      for(int j = 0, jj = 0; j < 5 && jj < 5; j++, jj++) {
        boat->boat[i][j] = boatInfo->boat[jj][ii];
      }
    }
  }

  return boat;
}


//função que coloca os barcos nos mapas
game_t* setupGame(game_t* game) {
  //selecionar opção manual ou random
  int opt = 0;
  printf("Setup manual ou random?\n");
  printf("Manual: 1\nRandom: 2\n");
  while(1) {
    int result = scanf("%i", &opt);
    while(getchar() != '\n');
    if((opt != 1 && opt != 2) || result < 1) {
      printf("Input inválido, tente novamente.\n");
      continue;
    }
    break;
  }
  int size = game->player1->size;
  game->boats = setupBoats(game, size, opt);
  system("clear");
  if(opt == 1) {
    printf("Prima enter começar setup do player 1.");
    while(getchar() != '\n');
  }
  game->player1 = setupMap(game, 1, opt);
  system("clear");
  if(opt == 1) {
    printf("Prima enter começar setup do player 2.");
    while(getchar() != '\n');
  }
  game->player2 = setupMap(game, 2, opt);


  return game;
}


//função que gera os barcos a colocar no mapa
boats_t* setupBoats(game_t* game, int size, int opt) {

  //pointer para não ter que escrever sempre game->boats...
  boats_t* boats = game->boats;

  //variável com o numero maximo possivel de barcos dado o tamanho
  int nboatsmax = size*size/25;
  //variável com o numero de barcos que os jogadores escolhem
  int nboats = 0;
  //variável com o id do barco que está a ser incrementado
  int id = 0;
  //variável com o número de barcos a adicionar ao barco escolhido em id
  //no caso do setup random esta variaável não é usada, adiciono um barco
  //de cada vez para evitar casos em que existam muitos barcos de um tipo e 0 de outros
  int num = 0;
  //variável que guarda o número de barcos que falta adicionar
  int boatsaux = 0;

  //opção manual
  if(opt == 1) {
    printf("Quantos barcos gostariam de ter?\n");
    printf("O número máximo de barcos é de %i.\n", nboatsmax);
    while(1){
      int result = scanf("%i", &nboats);
      while(getchar() != '\n');
      if(nboats <= 0 || nboats > size*size/25 || result < 1) {
        printf("Input inválido, tente novamente.\n");
        continue;
      }
      break;
    }

    //iniciar o numero de barcos a 0 e numero de barcos
    //total no numero escolhido pelo player
    {
      for(int i = 0; i < 6; i++) {
        boats->nID[i] = 0;
      }
      boats->nboats = nboats;
    }
    boatsaux = nboats;

    //colocação dos barcos
    while(boatsaux > 0){
      system("clear");
      printBoatTypes(game->boatsInfo);

      //stats atuais
      printf("(1) Número de Cruisers: %i\n",boats->nID[1]);
      printf("(2) Número de Battleships: %i\n", boats->nID[2]);
      printf("(3) Número de AircraftCarriers: %i\n", boats->nID[3]);
      printf("(4) Número de Bombers: %i\n", boats->nID[4]);
      printf("(5) Número de Destroyers: %i\n", boats->nID[5]);

      printf("Tem %i barcos para colocar.\n", boatsaux);

      while(1) {
        printf("Insira o identificador do barco e o número de barcos a inserir:\n");
        int result = scanf("%i %i", &id, &num);
        while(getchar() != '\n');
        //caso de valor inserido invalido
        if(id < 1 || id > 5 || num < 1 || num > boatsaux || result < 2) {
          printf("Input inválido, tente novamente.\n");
          continue;
        }
        break;
      }

      //retirar ao total de barcos que falta adicionar
      //o número de barcos a ser adicionado agora
      boatsaux -= num;
      //incrementar o total do barco escolhido no caso de input válido
      boats->nID[id] += num;
    }
  }

  //opção random
  if(opt == 2) {

    //número de barcos a colocar no caso de ser random
    //está entre 5 e nboatsmax;
    nboats =rand()%(nboatsmax-4)+5;
    //iniciar o numero de barcos a 0 e numero de barcos
    //total no numero definido acima
    {
      boats->nID[0] = 0;
      for(int i = 1; i < 6; i++) {
        boats->nID[i] = 1;
      }
      boats->nboats = nboats;
    }

    for(int i = 0; i < nboats-5; i++) {
      //ID do barco a adicionar
      id = rand()%5+1;
      //adicionar um barco ao total de barcos do tipo id
      boats->nID[id]++;
    }
  }

  return boats;
}


//função que coloca os barcos no mapa
player_t* setupMap(game_t* game, int playerid, int opt) {
  //opt define se está em modo manual ou random
  //opt a 1 -> manual, 2 -> random
  //pointer para o player que estamos a dar setup
  player_t* player;
  if(playerid == 1) {
    player = game->player1;
  }
  else {
    player = game->player2;
  }
  //pointer para os boats para nao ter que escrever sempre o game->...
  boats_t* boats = game->boats;

  //variavel que diz qual o id do barco a colocar
  int id = 0;
  //quantidade de barcos ja colocados de cada tipo
  int number[6] = {0};
  //variaveis para as informações sobre posição
  //e rotação do barco
  int x = -1, y = -1, dir = -1;
  //variavel para verificar se o
  bool valid = false;

  //colocar barcos no caso de ser manual
  if(opt == 1) {

    for(int i = 0; i < boats->nboats; i++) {
      id = 0;
      x = -1, y = -1, dir = -1;
      valid = false;
      system("clear");
      if(playerid == 1) {
        printf("Setup do player 1\n");
      }
      else {
        printf("Setup do player 2\n");
      }
      printMap(player, 1);
      printBoatTypes(game->boatsInfo);

      printf("(1) Cruisers\n\tTotal: %i\tFaltam: %i\n", boats->nID[1], (boats->nID[1]-number[1]));
      printf("(2) Battleships\n\tTotal: %i\tFaltam: %i\n", boats->nID[2], (boats->nID[2]-number[2]));
      printf("(3) AircraftCarriers\n\tTotal: %i\tFaltam: %i\n", boats->nID[3], (boats->nID[3]-number[3]));
      printf("(4) Bombers\n\tTotal: %i\tFaltam: %i\n", boats->nID[4], (boats->nID[4]-number[4]));
      printf("(5) Destroyers\n\tTotal: %i\tFaltam: %i\n", boats->nID[5], (boats->nID[5]-number[5]));

      while(1) {
        printf("Insira o id do barco que quer colocar:");
        int result = scanf("%i", &id);
        while(getchar() != '\n');
        //caso de input invalido
        if(id < 1 || id > 5 || result < 1) {
          printf("Input inválido, tente novamente.\n");
          continue;
        }
        //caso de escolher um barco sem barcos por colocar
        else if(boats->nID[id]-number[id] == 0) {
          printf("Já colocou todos os barcos desse tipo, escolha outro id.\n");
          continue;
        }
        //caso valido
        else {
          break;
        }
      }

      while(valid == false) {
        printf("Insira as cordenadas (primeiro o x e depois o y) e a rotação do barco.\n");
        printf("Direção:  0 -> padrão  1 -> 90º  2 -> 180º  3 -> 270º\n");

        while(1) {
          int result = scanf("%i %i %i", &x, &y, &dir);
          if( x < 0 || x >= player->size || y < 0 || y >= player->size || dir < 0 || dir > 3 || result < 3) {
            printf("Input inválido, tente novamente.");
            continue;
          }
          break;
        }

        //dar init ao boat apenas quando sei que o id e dir é valido
        boat_t* boat = initBoat(&(game->boatsInfo[id]), dir);

        //verificar se posso colocar o barco na posição
        valid = verify(player, x, y, boat);
        if(valid == false) {
          printf("Não foi possível colocar o barco ai, tente novas cordenadas ou direção.\n");
          continue;
        }
        else {
          player = addBoat(player, x, y, boat);
          //aumentar o HP no total de cells que o barco cobre
          player->HP += game->boatsInfo[id].boatHP;
          number[id]++;
          valid = true;
        }
      }
    }

  }


  //colocar barcos no caso de ser random
  if(opt == 2) {

    for(int i = 0; i < boats->nboats; i++) {
      id = 0;
      //definir qual barco colocar
      {
        if(number[1] < boats->nID[1]) {
          id = 1;
          number[id]++;
        }
        else if(number[2] < boats->nID[2]) {
          id = 2;
          number[id]++;
        }
        else if(number[3] < boats->nID[3]) {
          id = 3;
          number[id]++;
        }
        else if(number[4] < boats->nID[4]) {
          id = 4;
          number[id]++;
        }
        else if(number[5] < boats->nID[5]) {
          id = 5;
          number[id]++;
        }
      }

      x = -1;
      y = -1;
      dir = rand()%4;;
      valid = false;
      boat_t* boat = initBoat(&(game->boatsInfo[id]), dir);

      //ciclo que verifica a possibilidade
      //de colocar o barco na posição
      while(valid == false) {
        //cordenadas do inicio do barco
        x = rand()%(player->size);
        y = rand()%(player->size);
        //direção 0 para cima, 1 para a direita...
        valid = verify(player, x, y, boat);
      }
      //colocar barco depois de verificar
      player = addBoat(player, x, y, boat);
      //aumentar o HP no total de cells que o barco cobre
      player->HP += game->boatsInfo[id].boatHP;
    }
  }

  return player;
}


//função para printar o mapa
//flag = 1 é para printar mapa com tudo
//flag = 2 é para printar a visão do inimigo
void printMap(player_t* player, int flag) {
  //flag = 1 é para printar mapa com tudo
  //flag = 2 é para printar a visão do inimigo

  for(int i = player->size-1; i >= 0; i--) {
    printf("%3i|", i);
    for(int j = 0; j < player->size; j++) {
      if(flag == 2) {
        if(player->MAP[j][i].state == '#') {
          printf("   ");
          continue;
        }
      }
      //if necessario para printar os tipos de barcos diferentes
      //com letras diferentes sem guardar essa informação no
      if(player->MAP[j][i].state == '#') {
        printf("%3c", player->MAP[j][i].boat->boatChar);
      }
      else {
        printf("%3c", player->MAP[j][i].state);
      }
    }
    printf("\n");
  }
  printf("    ");
  for(int i = 0; i < player->size*3; i++) {
    printf("‾");
  }
  printf("\n");

  printf("    ");
  for(int i = 0; i < player->size; i++) {
    printf("%3i", i);
  }
  printf("\n");
}


//função para printar as formas dos barcos
void printBoatTypes(boatInfo_t* boatsInfo) {
  printf("Formato dos barcos:\n");
  printf(" (1) \t (2) \t (3) \t (4) \t (5) \n");
  for(int i = 4; i >= 0; i--) {
    for(int j = 1; j < 6; j++) {
      for(int k = 0; k < 5; k++) {
        if(boatsInfo[j].boat[k][i] == '#') {
          printf("%c", boatsInfo[j].boatChar);
        }
        else {
          printf(" ");
        }
      }
      printf("\t");
    }
    printf("\n");
  }
  printf("\n");
}


//função para verificar se se pode colocar o barco
bool verify(player_t* player, int x, int y, boat_t* boat) {
  // int xaux = x-2;
  // int yaux = y-2;
  for(int i = 0, xaux = x-2; i < 5; i++, xaux++) {
    for(int j = 0, yaux = y-2; j < 5; j++, yaux++) {

      if(boat->boat[i][j] == ' ') {
        continue;
      }
      if(xaux < 0 || xaux >= player->size || yaux < 0 || yaux >= player->size) {
        return false;
      }
      if(player->MAP[xaux][yaux].state == '#') {
        return false;
      }
    }
    printf("\n");
  }

  return true;
}


//função que adiciona barco ao mapa
player_t* addBoat(player_t* player, int x, int y, boat_t* boat) {
  //atualizar as cordenadas do centro do barco
  boat->x = x;
  boat->y = y;

  for(int i = 0, xaux = x-2; i < 5; i++, xaux++) {
    for(int j = 0, yaux = y-2; j < 5; j++, yaux++) {

      if(xaux < 0 || xaux >= player->size || yaux < 0 || yaux >= player->size) {
        continue;
      }
      if(boat->boat[i][j] != ' ') {
        player->MAP[xaux][yaux].state = '#';
        player->MAP[xaux][yaux].boat = boat;
      }
    }
  }

  return player;
}


//função para disparar
player_t* shoot(player_t* shootee) {
  int x = -1;
  int y = -1;
  printf("Insira as cordenadas a disparar.");
  scanf("%i %i", &x, &y);
  while(x < 0 || x >= shootee->size || y < 0 || y >= shootee->size) {
    printf("Cordenadas inválidas, insira outras.");
    scanf("%i %i", &x, &y);
  }

  char wtv;
  scanf("%c", &wtv);
  while(wtv != '\n') {
    scanf("%c", &wtv);
  }
  if(shootee->MAP[x][y].state == '0' || shootee->MAP[x][y].state == 'X') {
    printf("Já tinha disparado aí, mais atenção na próxima!\n");
    return shootee;
  }
  if(shootee->MAP[x][y].state == ' ') {
    printf("A sua bala falhou!\n");
    shootee->MAP[x][y].state = '0';
    return shootee;
  }

  //se as duas condições falharam, quer dizer que acertou
  //um barco numa posição que ainda nao tinha acertado
  //então atualizamos as informações de jogo
  //pointer para não ter que escrever sempre shootee->...
  boat_t* boat = shootee->MAP[x][y].boat;
  shootee->MAP[x][y].state = 'X';
  int subx = boat->x - x;
  int suby = boat->y - y;
  boat->boat[2-subx][2-suby] = 'X';
  boat->boatHP--;
  shootee->HP--;
  if(boat->boatHP == 0) {
    printf("Acertou num barco e afundou-o!\n");
  }
  else{
    printf("Acertou num barco!\n");
  }
  return shootee;
}


//função que liberta a memoria usada pelo jogo
void freeGame(game_t* game) {
  //free ao boatsInfo
  free(game->boatsInfo);

  //free ao boats
  free(game->boats);

  //dar free ao mapa do player1
  for(int i = game->player1->size-1; i >= 0; i--) {
    for(int j = game->player1->size-1; j >= 0; j--) {
      //caso exista um barco nesta posição
      //por dar free, faze-lo
      if(game->player1->MAP[i][j].boat != NULL) {
        free(game->player1->MAP[i][j].boat);
        game->player1->MAP[i][j].boat = NULL;
      }
    }
    free(game->player1->MAP[i]);
  }
  free(game->player1->MAP);

  //dar free ao mapa do player2
  for(int i = game->player2->size-1; i >= 0; i--) {
    for(int j = game->player2->size-1; j >= 0; j--) {
      //caso exista um barco nesta posição
      //por dar free, faze-lo
      if(game->player2->MAP[i][j].boat != NULL) {
        free(game->player2->MAP[i][j].boat);
        game->player2->MAP[i][j].boat = NULL;
      }
    }
    free(game->player2->MAP[i]);
  }
  free(game->player2->MAP);

  //dar free aos dois players
  free(game->player1);
  free(game->player2);

  //dar free ao jogo em si
  free(game);
}
