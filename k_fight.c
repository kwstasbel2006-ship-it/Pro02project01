#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void fight(char command, char **board){
    printf("FIGHT !!\n");
    char ch;
    int scanCheck;
    if (command == 'p'){
        char a, tempB;
        int b;
        scanCheck = scanf(" %c%d",&a,&b);
        if (scanCheck==2 && isValidPlasmagunCommand(a,b)){
            b--;
            plasmagun(board , a, b);
        }else {
            printf("error");
        }
    }else{
        int a, b;
        char tempA,tempB;
        scanf(" %c,%c",&tempA ,&tempB);
        a=charToNumber(tempA);
        b=charToNumber(tempB);
        a--;
        b--;
        if(command=='b'){
            bomb(board , a, b);
        }else{
            if (isValidNeurogunShot(board,a,b)){
                neurogun(board , a, b);
            }
        }

    }
}


void neurogun(char **board ,int x ,int y){
    char targetedZombie = board[x][y];
    board[x][y]='.';
    char tempX=x, tempY=y;
    tempY=y+1;
    if (isInsideTheBoard(x, tempY) && isSameTypeZombie(targetedZombie,board[x][tempY])){
        neurogun(board, x, tempY);
    }
    tempY=y-1;
    if (isInsideTheBoard(x, tempY) && isSameTypeZombie(targetedZombie,board[x][tempY])){
        neurogun(board, x, tempY);
    }
    tempX=x+1;
    if (isInsideTheBoard(tempX, y) && isSameTypeZombie(targetedZombie,board[tempX][y])){
        neurogun(board, tempX, y);
    }
    tempX=x-1;
    if (isInsideTheBoard(tempX, y) && isSameTypeZombie(targetedZombie,board[tempX][y])){
        neurogun(board, tempX, y);
    }
}


void bomb(char **board ,char x,char y){

}

void plasmagun(char **board ,char direction,char x){

}

void soundThing(char **board,SoundDirection currentSound){
    printf("sound  movement\n");
}

int isSameTypeZombie(char targetedZombie, char zombie){
    if (targetedZombie==zombie){
        return 1;
    }
    return 0;
}

int theZombieBelongsToAGroup(char **board ,char x ,char y){
    char theZombie = board[x][y];

    if (isInsideTheBoard(x, y + 1) && board[x][y + 1] == theZombie) 
        return 1;
    if (isInsideTheBoard(x, y - 1) && board[x][y - 1] == theZombie) 
        return 1;
    if (isInsideTheBoard(x + 1, y) && board[x + 1][y] == theZombie) 
        return 1;
    if (isInsideTheBoard(x - 1, y) && board[x - 1][y] == theZombie) 
        return 1;
    
    return 0;
}

int isValidNeurogunShot(char **board, char x, char y){
    if (isZombie(board[x][y])){
        if(theZombieBelongsToAGroup(board,x,y)){
            return 1;
        }
    }
    return 0;
}

int thereIsSomeValidNeurogunShot(char **board){
    int i,j;
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            if(isValidNeurogunShot(board,i,j))
                return 1;
        }
    }
    return 0;
}

int isValidPlasmagunCommand(char direction,char x){
    
}


int isInsideTheBoard(int x ,int y){
    if (x>=0 && x<= rows-1){
        if (y>=0 && y<= cols-1){
            return 1;
        }
    }
    return 0; 
}