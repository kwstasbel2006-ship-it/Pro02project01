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


void soundThing(char **board,SoundDirection currentSound){
    printf("sound movement: %s\n", soundNames[currentSound]);
    if(currentSound==DOWN){    
        int i,j,x;

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
    }
}