#ifndef LIBRARY_H
#define LIBRARY_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

#define MIN_ROWS 5
#define MIN_COLS 5
#define MAX_ROWS 35
#define MAX_COLS 35
//alekos's varaiables

typedef enum { UP, DOWN, LEFT, RIGHT } SoundDirection;
extern SoundDirection currentsound;
extern char **board;        
extern int rows, cols;
extern int score;       
extern int level;

//alekos's functions

void createboard();
void free_board();
void displayboard();

//==========================================================================

//kostas's functions 
void print(char **board);
void freeBoard(char **board);
int isFightCommand(char command);
char toLowercase(char command);
int countOfAliveZombies(char **board);
int isZombie(char z);
void fight(char command, char **board);
void creationOfTheTestBoard();

#endif