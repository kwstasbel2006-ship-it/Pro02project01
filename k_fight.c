#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void fight(char command, char **board){
    printf("FIGHT !!\n");
    char ch;
    //while(((!(ch = getchar()) >='1' && !(ch <='9'))) && ch != EOF);
    printf("befortheif\n");
    if (command == 'p'){
        char a, tempB;
        int b;
        printf("beforthescanf\n");
        scanf(" %c%d",&a,&b);
        // a=getchar();
        // tempB=getchar();
        // tempB = toLowercase(tempB);
        // b = charToNumber(tempB);
        plasmagun(board , a, b);
    }else{
        int a, b;
        char tempA,tempB;
        printf("beforthescanf\n");
        scanf(" %d, %d",&a ,&b);
        // tempA=getchar();
        // tempA = toLowercase(tempA);
        // a = charToNumber(tempA);
        // while(((!(ch = getchar()) >='1' && !(ch <='9'))) && ch != EOF);
        // tempB=getchar();
        // tempB = toLowercase(tempB);
        // b = charToNumber(tempB);
        if(command=='b'){
            bomb(board , a, b);
        }else{
            if (isValidNeurogunShot(board,a,b)){
                neurogun(board , a-1, b-1);
            }
        }

    }
}


void neurogun(char **board ,char x ,char y){
    char targetedZombie = board[x][y];
    board[x][y]='.';
    char tempX=x, tempY=y;
    tempY=y+1;
    if (isSameTypeZombie(targetedZombie,board[x][tempY])){
        neurogun(board, x-1, tempY-1);
        tempY=y-1;
    }else if (isSameTypeZombie(targetedZombie,board[x][tempY])){
        neurogun(board, x-1, tempY-1);
        tempX=x+1;
    }else if (isSameTypeZombie(targetedZombie,board[tempX][y])){
        neurogun(board, tempX-1, y-1);
        tempX=x-1;
    }else if (isSameTypeZombie(targetedZombie,board[tempX][y])){
        neurogun(board, tempX-1, y-1);
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
    if ((board[x][y+1]==theZombie)||(board[x][y-1]==theZombie)||(board[x+1][y]==theZombie)||(board[x-1][y]==theZombie)){
        return 1;
    }
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