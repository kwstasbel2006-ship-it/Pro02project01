#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>    

#define MIN_ROWS 5
#define MIN_COLS 5

typedef enum { UP, DOWN, LEFT, RIGHT } SoundDirection; //εδω οριζουμε τις κατευθυνσεις του ηχου σαν μια μεταβλητη
SoundDirection currentsound;

char **board;        
int rows, cols;      
int score = 0;       
int level = 1;
void createboard() //δημιουργία ταμπλό
{
    board = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) 
    {
        board[i] = (char *)malloc(cols * sizeof(char));
        for (int j = 0; j < cols; j++) 
        {
            double probabilities = 0.20; // Βασική πιθανότητα 20%
            if ((j > 0 && board[i][j-1] == '#') || (i > 0 && board[i-1][j] == '#')) 
            {
                probabilities = 0.40; // Αν υπάρχει γείτονας, το όριο γίνεται 40%
            }
            double r = (double)rand() / RAND_MAX; 
            if (r < probabilities) 
            {
                board[i][j] = '#'; 
            }
            else
                board[i][j] = (rand() % 9 + 1) + '0'; // 80% πιθανότητα για zombie

        }
    }
    currentsound = rand() % 4; // Τυχαία κατεύθυνση ήχου

}

void free_board() //απελευθέρωση μνήμης απο τον πίνακα
{
    for (int i =0; i <rows; i++)
        free(board[i]); // Απελευθέρωση κάθε γραμμής
    free(board); //απελευθέρωση κάθε διεύθυνσης που οδηγούν στις γραμμές

}

void displayboard() // Εμφάνιση του ταμπλό
{
    printf("\n--- ΕΠΙΠΕΔΟ %d | ΣΚΟΡ: %d ---\n", level, score);
    printf("    "); // Εμφάνιση κενής γραμμής για σωστή στοίχιση
    for (int j = 0; j < cols; j++) // Εμφάνιση αριθμών στηλών
    {
         printf("%2d _ ", j);
         printf("\n");
    }
    for (int i = 0; i < rows; i++) // Εμφάνιση αριθμών γραμμών
    {
        printf("%2d |", i);
        for (int j = 0; j < cols; j++) // Εμφάνιση περιεχομένου του ταμπλό
        {
            printf(" %c ", board[i][j]); 
            printf("\n");
        }
    
    }
}
    


