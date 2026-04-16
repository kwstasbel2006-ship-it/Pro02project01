#include"library.h"
#include<stdio.h>

SoundDirection currentsound;
char **board;        
int rows, cols;      
int score = 0;       
int level = 1;

int main (void){
    printf("helow kyrie kosta");    //alekos 2,3,5
                                    //kvstas 1,4
    printf("\nwrite a to test alekos and k to test kostas\n");
    char test;
    scanf("%c",&test);
    if(test == 'a'){          //TESTARISMATA ALEKOS
        rows=7;
        cols=8;
        createboard();
        displayboard();
        print(board);
        free_board();
    }else if(test == 'k'){    //TESTARISMATA KOSTAS
        creationOfTheTestBoard();
        freeBoard(board);
    }else{                  //the actual program 
        char command = '!';
        creationOfTheTestBoard();
        while((command != 'x')&&(rows<=35)&&(cols<=35)){
            //creation of the board
            //sound thing
            //new city created             
            while ((command != 'x')&&(countOfAliveZombies(board)>0)){
                print(board);
                scanf("%c",&command);
                if (isFightCommand(command))
                    fight(toLowercase(command),board);
                else
                    break;
            }
            freeBoard(board);
        }
    }
    
    return 0;
}