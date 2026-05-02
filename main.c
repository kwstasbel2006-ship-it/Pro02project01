#include"library.h"
#include<stdio.h>

SoundDirection currentSound;
char **board;        
int rows, cols;      
int score = 0;       
int level = 1;

const char* soundNames[] = {"UP", "DOWN", "LEFT", "RIGHT"};

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
        int scanCheck;
        int clearTheKeyboard;
        level = 1;
        rows=7;
        cols=7;        
        while((command != 'x')&&(rows<=35)&&(cols<=35)){
            createboard();
            //sound thing 
            //new city created
            while ((command != 'x')&&(countOfAliveZombies(board)>0)){
                print(board);
                scanCheck = scanf(" %c",&command);
                //printf("%c",command);
                command=toLowercase(command);
                if (scanCheck == 1 && isFightCommand(command)){
                    fight(command ,board);
                    print(board);
                    soundThing(board,currentSound);
                }else if(command == 'x'){
                    break;
                }else {
                    printf("Not valid command try again\n");
                    while ((clearTheKeyboard = getchar()) != '\n' && clearTheKeyboard != EOF);
                }
            }
            level++ ;
            freeBoard(board);
        }
    }
    
    return 0;
}