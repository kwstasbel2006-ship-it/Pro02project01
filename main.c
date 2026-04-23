#include"library.h"
#include<stdio.h>

SoundDirection currentSound;
char **board;        
int rows, cols;      
int score = 0;       
int level = 1;

int main (void){
    srand(time(NULL));
    printf("helow kyrie kostas");    //alekos 2,3,5
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
        //creationOfTheTestBoard();
        rows=MAX_ROWS;
        cols=MAX_COLS;
        createboard();
        print(board);
        freeBoard(board);
    }else{                  //the actual program 
        char command = '!' ;
        level = 1;
        rows=35;
        cols=35;
        while((command != 'x')&&(rows<=35)&&(cols<=35)){
            createboard();
            //sound thing 
            //new city created
            while ((command != 'x')&&(countOfAliveZombies(board)>0)){
                print(board);
                scanf(" %c",&command);
                //printf("%c",command);
                command=toLowercase(command);
                if (isFightCommand(command)){
                    fight(command ,board);
                }
            }
            level++ ;
            freeBoard(board);
        }
    }
    
    return 0;
}