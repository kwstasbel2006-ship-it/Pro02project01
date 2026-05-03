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
        rows=MIN_ROWS;
        cols=MIN_COLS;
        printf("\n========================================\n");
        printf("         THE OUTBREAK HAS BEGUN\n");
        printf("             LEVEL 1 START\n");
        printf("=========================================\n");
        while((command != 'x')&&(rows<=MAX_ROWS)&&(cols<=MAX_COLS)){
            createboard();
            printf("\n>>> The wind is howling %s through the empty streets...\n", soundNames[currentSound]);
            printf(">>> Any loud noises will draw the horde %s.\n", soundNames[currentSound]);
            //sound thing 
            //new city created
            while ((command != 'x')&&(countOfAliveZombies(board)>0)){
                print(board);
                
                printf("\nCOMMANDS: [n x,y] Neurogun | [b x,y] Bomb | [p l/r/u/d x] Plasma | [x] Quit\n");
                printf("Make your move Commander: ");

                scanCheck = scanf(" %c",&command);
                //printf("%c",command);
                command=toLowercase(command);
                if (scanCheck == 1 && isFightCommand(command)){
                    score += fight(command ,board);
                    print(board);
                    soundThing(board,currentSound);
                }else if(command == 'x'){
                    break;
                }else {
                    printf("Not valid command try again\n");
                    while ((clearTheKeyboard = getchar()) != '\n' && clearTheKeyboard != EOF);
                }
            }
            freeBoard(board);
            
            if (command != 'x'){
                level++ ;
                printf("\n========================================\n");
                printf("         CITY SECTOR CLEARED!\n");
                printf("  The military is moving you to a larger\n  and more dangerous sector...\n");
                printf("              Get ready.\n");
                printf("            MOVE TO LEVEL %d\n", level);
                printf("========================================\n\n");
            }
            rows++ ;
            cols++ ;
        }

        dramaticEndOfGame(command);
    }
    
    return 0;
}