#include<stdio.h>
#include"library.h"

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
        createboard();
        displayboard();
        free_board();
    }else if(test == 'k'){    //TESTARISMATA KOSTAS
        int i,j;
        char **board;
        board = malloc((7)*sizeof(char*));
		if(board==NULL)
			printf("ERROR 1");
		for(i=0;i<7;i++)
		{
			board[i]=malloc((8)*sizeof(char*));
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
        
        for(i = 0; i < 7; i++) {
            for(j = 0; j < 8; j++) {
                board[i][j] = template[i][j];
            }
        }
        
        print(board);
        
        
        freeBoard(board);
    }else{                  //the actual program 

    }
    
    //while (){
        
    //}
    return 0;
}