#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>    
#include "library.h"

#define MIN_ROWS 5
#define MIN_COLS 5
#define MAX_ROWS 35
#define MAX_COLS 35

/*char **board;        
int rows, cols;      
int score = 0;     
int level = 1;       
SoundDirection current_sound;*/ 

void createboard() //δημιουργία ταμπλό
{
    board = (char **)malloc(rows * sizeof(char *));
    for (int i=0; i<rows; i++) 
    {
        board[i] = (char *)malloc(cols * sizeof(char));
        for (int j=0; j<cols; j++) 
        {
            double probabilities = 0.20; // Βασική πιθανότητα 20%
            if ((j>0 && board[i][j-1] == '#') || (i>0 && board[i-1][j] == '#')) 
            {
                probabilities=0.40; 
            }
            double r=(double)rand() / RAND_MAX; 
            if (r<probabilities) 
            {
                board[i][j] = '#'; 
            }
            else
                board[i][j]=(rand()%9+1) + '0'; // 80% πιθανότητα για zombie

        }
    }
    currentSound= rand()%4; // Τυχαία κατεύθυνση ήχου

}

void free_board() //απελευθέρωση μνήμης απο τον πίνακα
{
    for (int i=0; i<rows; i++)
        free(board[i]); // Απελευθέρωση κάθε γραμμής
    free(board); //απελευθέρωση κάθε διεύθυνσης που οδηγούν στις γραμμές

}

void displayboard() // Εμφάνιση του ταμπλό
{
    printf("\n--- EPIPEDO %d | SCORE: %d ---\n", level, score);
    printf("    "); // Εμφάνιση κενής γραμμής για σωστή στοίχιση
    for (int j=0; j<cols; j++) 
    {
         printf("%2d ", j);
    }
    printf("\n");
    for (int i=0; i<rows; i++)  
    {
        printf("%2d |", i);
        for (int j=0; j<cols; j++) // Εμφάνιση περιεχομένου του ταμπλό
        {
            printf("%c", board[i][j]); 
        }
    printf("\n");
    
    }
}

void level_up (char ***board, int *rows, int *cols, int *level) 
{
    int zombies_found=0;
    for (int i=0; i<*rows; i++) 
    {
        for (int j=0; j<*cols; j++) 
        {
            if ((*board)[i][j]>='1' && (*board)[i][j]<='9') 
            {
                zombies_found==1;
                break; 
            }
        }
        if (zombies_found==1) break;
    }

    if (zombies_found==0)
    {
        printf("\n--- GOOD JOB, LEVEL UP! ---\n");
            
        free_board(*board, *rows);

        (*level)++;
        (*rows)++;
        (*cols)++;

        createboard();
    }
}

int calculate_move_score(int zombies_killed, int level)
{
    int total_score, command;
    if (command == 'x' || command == 'X') {
        printf("\n==========================================\n");
        printf("        PLAYER REPORT               \n");
        printf("============================================\n");
        printf("earned levels: %d\n", level-1);
        printf("total score: %d\n", total_score); //αρχικοποιηση στην main το total score
        printf("------------------------------------------\n");


        printf("You are running out of power...\n");
        printf("The guns are emptying and the darkness is approaching..\n"); 
        printf("bye player, i hope you comeback again:)\n");
        printf("==========================================\n");


        free_board(board, rows);
        exit(0); 
    }

    return (zombies_killed * zombies_killed) * level;
}



    


