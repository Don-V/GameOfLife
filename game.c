#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define nRows 24
#define nCols 80

void printWorld();
int countLivingNeigbours(int x, int y);
int checkForLife();

char world[nRows][nCols];
const char LIFE = 'O';
const char DEAD = ' ';

int main(int argc, char *argv[]){
  int i,j;
  char nextWorld[nRows][nCols];
  int wTime = 0;
  
  for (i = 0; i < nRows; i++){
    for (j = 0; j < nCols; j++){
      world[i][j] = DEAD;//TODO change to space
      nextWorld[i][j] = DEAD;
    }
  }
  
  for (i = 1; i < argc; i+=2){
    int p = atoi(argv[i]);
    if (p >= nCols) p = p - nCols;
    else if (p < 0) p = nCols + p;
    int q = atoi(argv[i+1]);
    if (q >= nRows) q = q - nRows;
    else if (q < 0) q = nRows + q;
    world[q][p] = LIFE;
  }
  
  while(checkForLife()){
    printWorld();
    for (i = 0; i < nRows; i++){
      for (j = 0; j < nCols; j++){
        char current = world[i][j];
        
        if(current == LIFE){
          if (countLivingNeigbours(j, i) == 0 || countLivingNeigbours(j, i) == 1) nextWorld[i][j] = DEAD;
          else if (countLivingNeigbours(j, i) == 2 || countLivingNeigbours(j, i) == 3) nextWorld[i][j] = LIFE;
          else if (countLivingNeigbours(j, i) == 4) nextWorld[i][j] = DEAD;
        }
        else if(current == DEAD && countLivingNeigbours(j, i) == 3) nextWorld[i][j] = LIFE;
        // printf("i j: %d %d\n", i, j);
      }
    }
    memcpy(world, nextWorld, sizeof(char)*nRows*nCols);
    memset(nextWorld, 0, sizeof(char)*nRows*nCols);//TODO change 32 to an ascii change
    printf("Time: %d\n", ++wTime);
    usleep(83333/3000);
  }
  return 0;
}

void printWorld(){
  int i = 0, j = 0;
  for (i = 0; i < nRows; i++){
    for (j = 0; j < nCols; j++){
      printf("%c", world[i][j]);
    }
    printf("\n");
  }
}

int countLivingNeigbours(int x, int y){
  int result = 0;
  int startX = (x - 1 < 0) ? -1: x-1, endX = (x + 1 >= nCols) ? -1: x+1;
  int startY = (y - 1 < 0) ? -1: y-1, endY = (y + 1 >= nRows) ? -1: y+1;
  int i = 0, j = 0;
  // printf("x: %d, y: %d\n", x, y);
  for (i=startY; i <= endY; i++){
    for (j=startX; j <= endX; j++){
      if (!(i== y && j == x) && i != -1 && j != -1){
        if (world[i][j] == LIFE) {result++;/*world[i][j] = 'X';*/}//TODO reduce
      }
    }
  }
  return result;
}

// printf("world[%d][%d] = %c\n", i, j, world[j][i]);

int checkForLife(){
  int i = 0, j = 0;
  for (i = 0; i < nRows; i++){
    for (j = 0; j < nCols; j++){
      if (world[i][j] == LIFE) return 1;
    }
  }
  return 0;
}