#include<stdio.h>
#include"library.h"
// void soundThing(char **board, SoundDirection currentSound) {
//     printf("sound movement DOWN\n");
//     int i, j, target_row;

//     // Loop through every column independently
//     for (j = 0; j < cols; j++) {
        
//         // Start target_row at the very bottom
//         target_row = rows - 1; 

//         // Scan upwards from the bottom
//         for (i = rows - 1; i >= 0; i--) {
            
//             // If we hit a building, the 'floor' resets to just above the building!
//             if (board[i][j] == '#') {
//                 target_row = i - 1; 
//             } 
//             // If we find a zombie, and it needs to fall...
//             else if (isZombie(board[i][j])) {
//                 // Only move it if the target row is actually below it
//                 if (target_row > i) {
//                     board[target_row][j] = board[i][j]; // Move it down
//                     board[i][j] = '.';                  // Clear old spot
//                 }
//                 // Once a zombie lands, the next available space is one row higher
//                 target_row--; 
//             }
//         }
//     }
//}

//j is the empty hole "."
//x is the scanner looking for a zombie
void soundThing(char **board,SoundDirection currentSound){
    printf("sound movement: %s\n", soundNames[currentSound]);
    int i,j,x;
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