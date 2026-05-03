#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int fight(char command, char **board){
    //printf("FIGHT !!\n");
    char ch;
    int scanCheck;
    int tempScore = 0 ;
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
                tempScore = plasmagun(board, direction, a);
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
            
            if (a == -1 || b == -1) {
                printf("Invalid characters, Use 1-9 or A-Z or a-z \n");
                return 0;
            }
            a--;
            b--;
            
            if (command == 'b'){
                if (isValidBombShot(board,a, b)) {
                    tempScore = bomb(board, a, b);
                } else {
                    printf("\n>>> Commander, you are aiming outside the city limits! Pick a valid coordinate.\n");
                }               
            } else if(command == 'n') {

                if (!isInsideTheBoard(a, b)) {
                    printf("\n>>> Target out of bounds! Aim inside the grid.\n");
                }else if (thereIsSomeValidNeurogunShot(board)) {
                    if (isValidNeurogunShot(board, a, b)) {
                        
                        char targetZombie = board[a][b];
                        int numOfKills = neurogun(board, a, b, targetZombie);
                        int basicScore = numOfKills * charToNumber(targetZombie);
                        tempScore = scoreFunction(numOfKills, basicScore);

                        if (numOfKills >= 6) {
                            printf("\n>>> EPIDEMIC STRIKE! A massive chain of %d zombies collapsed! +%d pts <<<\n", numOfKills, tempScore);
                        } else {
                            printf("\n>>> Chain reaction successful! %d zombies neutralized. +%d pts <<<\n", numOfKills, tempScore);
                        }
                    } else {
                        printf("\n>>> Invalid target. Neuro-dart wasted on a solo zombie! <<<\n");
                    }
                } else {
                    printf("\n>>> There is no valid neurogun shot anywhere. Try a different weapon! <<<\n");
                }
            }
        } else {
            printf("Invalid input format, Use format like b 3,3 or n a,b\n");
        }
    }
    return tempScore;
}


int neurogun(char **board ,int x ,int y, char typeOfTheZombie){
    board[x][y]='.';
    char tempX=x, tempY=y;
    tempY=y+1;
    int numOfKilledZombies = 1;
    if (isInsideTheBoard(x, tempY) && isSameTypeZombie(typeOfTheZombie,board[x][tempY])){
        numOfKilledZombies += neurogun(board, x, tempY,typeOfTheZombie);
    }
    tempY=y-1;
    if (isInsideTheBoard(x, tempY) && isSameTypeZombie(typeOfTheZombie,board[x][tempY])){
        numOfKilledZombies += neurogun(board, x, tempY,typeOfTheZombie);
    }
    tempX=x+1;
    if (isInsideTheBoard(tempX, y) && isSameTypeZombie(typeOfTheZombie,board[tempX][y])){
        numOfKilledZombies += neurogun(board, tempX, y,typeOfTheZombie);
    }
    tempX=x-1;
    if (isInsideTheBoard(tempX, y) && isSameTypeZombie(typeOfTheZombie,board[tempX][y])){
        numOfKilledZombies += neurogun(board, tempX, y,typeOfTheZombie);
    }
    return numOfKilledZombies;
}

int isValidBombShot(char **board,int a, int b){
    if (isInsideTheBoard(a, b))
        return 1;
    return 0;
}

int bomb(char **board ,char x,char y){
    int basicScore = 0;
    int zombiesKilled = 0;
    int hitValue = 0;

    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            
            hitValue = bombShot(board, i, j);
            
            if (hitValue > 0) {
                basicScore += hitValue;
                zombiesKilled++;
            }
        }
    }
    // ... end of your nested loops ...

    int finalscore = scoreFunction(zombiesKilled, basicScore);

    // THE HYPE MESSAGES!
    if (zombiesKilled >= 5) {
        printf("\n>>> MASSIVE EXPLOSION! %d zombies blown to pieces! +%d pts <<<\n", zombiesKilled, finalscore);
    } else if (zombiesKilled > 0) {
        printf("\n>>> Boom! %d zombies eliminated. +%d pts <<<\n", zombiesKilled, finalscore);
    } else {
        printf("\n>>> The bomb hit nothing but concrete... 0 points. <<<\n");
    }

    return finalscore;
}

int bombShot(char **board, char x, char y){
    if (isInsideTheBoard(x, y) && isZombie(board[x][y])){
        int zombieValue = charToNumber(board[x][y]);
        board[x][y] = '.';
        return zombieValue;
    }
    return 0;
}

int plasmagun(char **board ,char direction,char x){
    int i;
    int basicScore = 0 ; 
    int numOfKilledZombies =0;
    if (direction == 'l'){
        for(i=0; i< cols ;i++){
            if(isZombie(board[x][i])){
                basicScore+=charToNumber(board[x][i]);
                numOfKilledZombies++;
                board[x][i]='.';
            }else if(board[x][i]=='#')
                break;
            else 
                continue;
        }
    }
    if (direction == 'r'){
        for(i=cols-1; i>= 0 ;i--){
            if(isZombie(board[x][i])){
                basicScore+=charToNumber(board[x][i]);
                numOfKilledZombies++;
                board[x][i]='.';
            }else if(board[x][i]=='#')
                break;
            else 
                continue;
        }
    }
    if (direction == 'u'){
        for(i=0; i< rows ;i++){
            if(isZombie(board[i][x])){
                basicScore+=charToNumber(board[i][x]);
                numOfKilledZombies++;
                board[i][x]='.';
            }else if(board[i][x]=='#')
                break;
            else 
                continue;
        }
    }
    if (direction == 'd'){
        for(i=rows-1; i>= 0 ;i--){
            if(isZombie(board[i][x])){
                basicScore+=charToNumber(board[i][x]);
                numOfKilledZombies++;
                board[i][x]='.';
            }else if(board[i][x]=='#')
                break;
            else 
                continue;
        }
    }
    int finalscore = scoreFunction(numOfKilledZombies, basicScore);

    if (numOfKilledZombies >= 4) {
        printf("\n>>> DEVASTATING BEAM! %d zombies vaporized! +%d pts <<<\n", numOfKilledZombies, finalscore);
    } else if (numOfKilledZombies > 0) {
        printf("\n>>> Clean shot. %d zombies down. +%d pts <<<\n", numOfKilledZombies, finalscore);
    } else {
        printf("\n>>> The plasma beam hit nothing but air... 0 points. <<<\n");
    }

    return finalscore;
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
    if (isInsideTheBoard(x,y) && isZombie(board[x][y])){
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
int scoreFunction (int numOfTheDeadZombies, int basicScore){
    if (numOfTheDeadZombies == 0) 
        return 0;

    double comboMultiplier = 1.0 + ((numOfTheDeadZombies - 1) * 0.25);
    return basicScore * comboMultiplier * (level*1.25);
}