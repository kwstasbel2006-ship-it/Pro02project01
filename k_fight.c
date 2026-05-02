#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void fight(char command, char **board){
    //printf("FIGHT !!\n");
    char ch;
    int scanCheck;
    if (command == 'p'){
        char direction, tempA;
        int a;
        
        scanCheck = scanf(" %c %c", &direction, &tempA);
        
        if (scanCheck == 2) {
            a = charToNumber(tempA);
            
            // Make sure the character was a valid letter/number
            if (a != -1 && isValidPlasmagunCommand(direction, a)) {
                a--;
                direction = toLowercase(direction);
                plasmagun(board, direction, a);
            } else {
                printf("Invalid Plasmagun parameters or out of bounds.\n");
            }
        } else {
            printf("Invalid input format, Use format like: p l7\n");
        }
    }else{
        int a, b;
        char tempA,tempB;
        scanCheck = scanf(" %c,%c",&tempA ,&tempB);
        if (scanCheck == 2) {
            a = charToNumber(tempA);
            b = charToNumber(tempB);
            
            if (a == -1 && b == -1) {
                printf("Invalid characters, Use 1-9 or A-Z or a-z \n");
                return;
            }
            a--;
            b--;
            
            if (command == 'b') {
                bomb(board, a, b);
            } else {
                if (thereIsSomeValidNeurogunShot(board)) {
                    if (isValidNeurogunShot(board, a, b)) {
                        neurogun(board, a, b);
                    } else {
                        printf("Invalid target Not a group \n");
                    }
                } else {
                    printf("There is no valid neurogun shot, try something else .\n");
                }
            }
        } else {
            printf("Invalid input format, Use format like b 3,3 or n a,b\n");
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
    bombShot(board,x,y);
    bombShot(board,x+1,y);
    bombShot(board,x,y+1);
    bombShot(board,x-1,y);
    bombShot(board,x,y-1);
    bombShot(board,x-1,y-1);
    bombShot(board,x+1,y-1);
    bombShot(board,x-1,y+1);
    bombShot(board,x+1,y+1);
}

void bombShot(char **board, char x, char y){
    if (isInsideTheBoard(x, y) && isZombie(board[x][y]))
        board[x][y]='.';
}

void plasmagun(char **board ,char direction,char x){
    int i;
    if (direction == 'l'){
        for(i=0; i< cols ;i++){
            if(isZombie(board[x][i]))
                board[x][i]='.';
            else if(board[x][i]=='#')
                break;
            else 
                continue;
        }
    }
    if (direction == 'r'){
        for(i=cols-1; i>= 0 ;i--){
            if(isZombie(board[x][i]))
                board[x][i]='.';
            else if(board[x][i]=='#')
                break;
            else 
                continue;
        }
    }
    if (direction == 'u'){
        for(i=0; i< rows ;i++){
            if(isZombie(board[i][x]))
                board[i][x]='.';
            else if(board[i][x]=='#')
                break;
            else 
                continue;
        }
    }
    if (direction == 'd'){
        for(i=rows-1; i>= 0 ;i--){
            if(isZombie(board[i][x]))
                board[i][x]='.';
            else if(board[i][x]=='#')
                break;
            else 
                continue;
        }
    }
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

int isValidPlasmagunCommand(char direction, int x) {
    direction = toLowercase(direction);

    if (direction != 'l' && direction != 'r' && direction != 'u' && direction != 'd') {
        return 0;
    }

    if (direction == 'l' || direction == 'r'){
        if (x >= 1 && x <= rows) 
            return 1;
    }else if (direction == 'u' || direction == 'd'){
        if (x >= 1 && x <= cols) 
            return 1;
    }
    return 0;
}


int isInsideTheBoard(int x ,int y){
    if (x>=0 && x<= rows-1){
        if (y>=0 && y<= cols-1){
            return 1;
        }
    }
    return 0; 
}