
#include <stdio.h>

void print(char **board);

int main (void){

    char board[7][8] = {
        {'2','2','1','9','8','4','8','3'},
        {'6','#','#','7','6','8','2','8'},
        {'8','4','#','1','8','3','8','5'},
        {'3','1','6','3','8','2','5','8'},
        {'9','3','4','3','7','#','#','8'},
        {'#','#','3','3','7','#','#','4'},
        {'1','6','3','5','7','4','3','1'}
    };
    
    print(&board);
    
    return 0;
}


void print(char **board)
{
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