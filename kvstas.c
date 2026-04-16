
#include <stdio.h>
#include <stdlib.h>

void print(char **board)
{
        printf("\n");
        printf("\n");

        int j, i;
        printf("     ");
        for (j = 0;j < 8;j++)
                printf("%3c",j+65);
        printf("\n");


        printf("------");
        for (j = 0;j < 8;j++)
                printf("---");
        printf("\n");

        for (i = 0;i < 7;i++){
                printf("%2d  |", i+1);
                for (j = 0;j < 8;j++)
                        printf("%3c", board[i][j]);
                printf("\n");
        }
        printf("\n");
}

void freeBoard(char **board) 
{
    int i;
    for(i = 0; i < 7; i++) {
        free(board[i]);
    }
    free(board);
}