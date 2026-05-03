#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void print(char **board)
{
        printf("\n");

        int j, i;
        printf("(x\\y)");
        for (j = 0;j < cols ;j++)
                printf("%3c",alphabet(j+1));
        printf("\n");


        printf("------");
        for (j = 0;j < cols ;j++)
                printf("---");
        printf("\n");

        for (i = 0;i < rows ;i++){
                printf("%2c  |",alphabet(i+1));
                for (j = 0;j < cols ;j++)
                        printf("%3c", board[i][j]);
                printf("\n");
        }
        printf("\n");
}

char alphabet(int i){
        if ((i>=0)&&(i<=9)){
                return i+'0';
        }else
                return i-10+'A';
}

void freeBoard(char **board){
    int i;
    for(i = 0; i < rows ; i++) {
        free(board[i]);
    }
    free(board);
}

int isFightCommand(char command){
    if (command == 'n'|| command == 'b'||command == 'p')
        return 1;
    else
       return 0;
}

char toLowercase(char command){
        return tolower(command);
}

int countOfAliveZombies(char **board){
        int count=0 , i, j;
        for (i = 0;i < rows ;i++){
                for (j = 0;j < cols ;j++){
                        if (isZombie(board[i][j]))
                                count++;
                }
        }
        return count;
}


int isZombie(char z){
        if(z>='1'&&z<='9')
                return 1;
        else 
                return 0;
}

int charToNumber(char ch){
        if (ch >= '0' && ch <= '9')
                return ch - '0'; 
        ch = toLowercase(ch);
        if (ch >= 'a' && ch <= 'z') {
                return (ch - 'a') + 10;
        }
        return -1;
}


void creationOfTheTestBoard(){
        int i,j;
        rows=7;
        cols=8;
        board = malloc((7)*sizeof(char*));
        if(board==NULL)
                printf("ERROR 1");
        for(i=0;i<rows;i++)
        {
                board[i]=malloc((cols)*sizeof(char*));
                if(board[i]==NULL)
                        printf("ERROR 1");
        }

        char template[7][8] = {
            {'2','2','1','9','8','4','8','3'},
            {'6','#','#','7','6','8','2','8'},
            {'8','4','#','1','8','3','8','5'},
            {'3','1','6','3','8','2','5','8'},
            {'9','3','4','3','7','#','#','8'},
            {'#','#','3','3','7','#','#','4'},
            {'1','6','3','5','7','4','3','1'}
        };
        
        for(i = 0; i < rows ; i++) {
            for(j = 0; j < cols ; j++) {
                board[i][j] = template[i][j];
            }
        }
        
        print(board);
}

void dramaticEndOfGame(char command){
        printf("\n================================================\n");
        printf("               END OF THE GAME\n");
        printf("===============================================\n");
        
        if (command == 'x') {
                printf("You chose to escape the fight... :( \n");
                printf("The zombies continue to run the entire earth.\n");
                printf("Humanity's last hope was YOU \n");
                printf("And now you fade into the FEARRr...\n");
        } else {
                printf("CONGRATULATIONS! You just eradicated the zombie outbreak!\n");
                printf("The hole planet are finally safe from the undead menace.\n");
                printf("Now humanity can return to normal, and safely proceed\n");
                printf("to destroy itself with World War III...\n");
                printf("        DAN DAN DAN...\n");
        }
        printf("--------------------------------------------------\n");
        printf("GAME INFO :\n");
        printf("Levels Completed  : %d\n", level - 1);
        printf("Final Score       : %d\n", score);
        printf("--------------------------------------------------\n");
}