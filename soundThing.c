#include<stdio.h>
#include"library.h"

void soundThing(char **board,SoundDirection currentSound){
printf("\n>>> WARNING: Acoustic sensors triggered. Horde migration: %s <<<\n", soundNames[currentSound]);    int i,j,x;
    switch(currentSound){
        case DOWN:
            for(j=0;j<cols; j++){
                for(i=rows-1;i>=0; i--){
                    if(board[i][j]!='.')
                        continue;
                    else {
                        for(x=i-1;x>=0; x--){
                            if (board[x][j]=='#'){
                                break;
                            } 
                            else if(isZombie(board[x][j])){
                                board[i][j] = board[x][j];
                                board[x][j] = '.';
                                break;
                            }
                        }
                    }
                }
            }
        break;
        case UP:
            for(j=0;j<cols; j++){
                for(i=0;i<rows; i++){
                    if(board[i][j]!='.')
                        continue;
                    else {
                        for(x=i+1;x<rows; x++){
                            if (board[x][j]=='#'){
                                break;
                            } 
                            else if(isZombie(board[x][j])){
                                board[i][j] = board[x][j];
                                board[x][j] = '.';
                                break;
                            }
                        }
                    }
                }
            }
        break;
        case LEFT:
            for(i=0;i<rows; i++){
                for(j=0;j<cols; j++){
                    if(board[i][j]!='.')
                        continue;
                    else {
                        for(x=j+1;x<cols; x++){
                            if (board[i][x]=='#'){
                                break;
                            } 
                            else if(isZombie(board[i][x])){
                                board[i][j] = board[i][x];
                                board[i][x] = '.';
                                break;
                            }
                        }
                    }
                }
            }
        break;
        case RIGHT:
            for(i=0;i<rows; i++){
                for(j=cols-1;j>=0; j--){
                    if(board[i][j]!='.')
                        continue;
                    else {
                        for(x=j-1;x>=0; x--){
                            if (board[i][x]=='#'){
                                break;
                            } 
                            else if(isZombie(board[i][x])){
                                board[i][j] = board[i][x];
                                board[i][x] = '.';
                                break;
                            }
                        }
                    }
                }
            }
        break;
    }
}