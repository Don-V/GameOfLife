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
      world[i][j] = DEAD;
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
      }
    }
    memcpy(world, nextWorld, sizeof(char)*nRows*nCols);
    memset(nextWorld, (int)DEAD, sizeof(char)*nRows*nCols);
    printf("Time: %d\n", ++wTime);
    usleep(83333);
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
  int i = 0, j = 0;
  for (i=y-1; i <= y+1; i++){
    for (j=x-1; j <= x+1; j++){
      if (!(i== y && j == x)){
        int a = (i < 0) ? i + nRows : i;
        int b = (j < 0) ? j + nCols : j;
        if (world[a%nRows][b%nCols] == LIFE) {result++;}
      }
    }
  }
  return result;
}

int checkForLife(){
  int i = 0, j = 0;
  for (i = 0; i < nRows; i++){
    for (j = 0; j < nCols; j++){
      if (world[i][j] == LIFE) return 1;
    }
  }
  return 0;
}