#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

#define MIN_ROWS 5
#define MIN_COLS 5
#define MAX_ROWS 35
#define MAX_COLS 35

//alekos's variables
typedef enum { UP, DOWN, LEFT, RIGHT } SoundDirection;

//alekos's functions

void createboard();
void free_board();
void displayboard();

//==========================================================================

//kostas's functions 
void print(char **board);
void freeBoard(char **board);
int isFightCommand(char command);
char toLowercase(char command);
int countOfAliveZombies(char **board);
int isZombie(char z);
int fight(char command, char **board);
void creationOfTheTestBoard();
void soundThing(char **board,SoundDirection currentSound);
int validCommand(char command);
char alphabet(int i);
int neurogun(char **board ,int a,int b, char typeOfTheZombie);
int bomb(char **board ,char a,char b);
int plasmagun(char **board ,char a,char b);
int theZombieBelongsToAGroup(char **board ,char x ,char y);
int isValidNeurogunShot(char **board, char x, char y);
int thereIsSomeValidNeurogunShot(char **board);
int theZombieBelongsToAGroup(char **board ,char x ,char y);
int isSameTypeZombie(char targetedZombie, char zombie);
int charToNumber(char ch);
int isInsideTheBoard(int x ,int y);
int isValidPlasmagunCommand(char direction, int x);
int bombShot(char **board, char x, char y);
void dramaticEndOfGame(char command);
int scoreFunction(int numOfTheDeadZombies, int basicScore);
int isValidBombShot(char **board,int a, int b);

//kostas variables
const char* soundNames[];

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




//========================================
//==============  alekos  ================

void createboard() //δημιουργία ταμπλό
{
    board = (char **)malloc(rows * sizeof(char *));
    for (int i=0; i<rows; i++) 
    {
        board[i] = (char *)malloc(cols * sizeof(char));
        for (int j=0; j<cols; j++) 
        {
            double probabilities = 0.20; // Βασική πιθανότητα 20%
            if ((j>0 && board[i][j-1] == '#') || (i>0 && board[i-1][j] == '#')) 
            {
                probabilities=0.40; 
            }
            double r=(double)rand() / RAND_MAX; 
            if (r<probabilities) 
            {
                board[i][j] = '#'; 
            }
            else
                board[i][j]=(rand()%9+1) + '0'; // 80% πιθανότητα για zombie

        }
    }
    currentSound= rand()%4; // Τυχαία κατεύθυνση ήχου

}

void free_board() //απελευθέρωση μνήμης απο τον πίνακα
{
    for (int i=0; i<rows; i++)
        free(board[i]); // Απελευθέρωση κάθε γραμμής
    free(board); //απελευθέρωση κάθε διεύθυνσης που οδηγούν στις γραμμές

}

void displayboard() // Εμφάνιση του ταμπλό
{
    printf("\n--- EPIPEDO %d | SCORE: %d ---\n", level, score);
    printf("    "); // Εμφάνιση κενής γραμμής για σωστή στοίχιση
    for (int j=0; j<cols; j++) 
    {
         printf("%2d ", j);
    }
    printf("\n");
    for (int i=0; i<rows; i++)  
    {
        printf("%2d |", i);
        for (int j=0; j<cols; j++) // Εμφάνιση περιεχομένου του ταμπλό
        {
            printf("%c", board[i][j]); 
        }
    printf("\n");
    
    }
}

void level_up (char ***board, int *rows, int *cols, int *level) 
{
    int zombies_found=0;
    for (int i=0; i<*rows; i++) 
    {
        for (int j=0; j<*cols; j++) 
        {
            if ((*board)[i][j]>='1' && (*board)[i][j]<='9') 
            {
                zombies_found==1;
                break; 
            }
        }
        if (zombies_found==1) break;
    }

    if (zombies_found==0)
    {
        printf("\n--- GOOD JOB, LEVEL UP! ---\n");
            
        free_board(*board, *rows);

        (*level)++;
        (*rows)++;
        (*cols)++;

        createboard();
    }
}

int calculate_move_score(int zombies_killed, int level)
{
    int total_score, command;
    if (command == 'x' || command == 'X') {
        printf("\n==========================================\n");
        printf("        PLAYER REPORT               \n");
        printf("============================================\n");
        printf("earned levels: %d\n", level-1);
        printf("total score: %d\n", total_score); //αρχικοποιηση στην main το total score
        printf("------------------------------------------\n");


        printf("You are running out of power...\n");
        printf("The guns are emptying and the darkness is approaching..\n"); 
        printf("bye player, i hope you comeback again:)\n");
        printf("==========================================\n");


        free_board(board, rows);
        exit(0); 
    }

    return (zombies_killed * zombies_killed) * level;
}



    


//=========================================================
//========================  kostas  =======================


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

void print(char **board)
{
        printf("\n");

        int j, i;
        printf("(x\\y)");
        for (j = 0;j < cols ;j++)
                printf("%3c",alphabet(j+1));
        printf("\n");


        printf("------");
        for (j = 0;j < cols ;j++)
                printf("---");
        printf("\n");

        for (i = 0;i < rows ;i++){
                printf("%2c  |",alphabet(i+1));
                for (j = 0;j < cols ;j++)
                        printf("%3c", board[i][j]);
                printf("\n");
        }
        printf("\n");
}

char alphabet(int i){
        if ((i>=0)&&(i<=9)){
                return i+'0';
        }else
                return i-10+'A';
}

void freeBoard(char **board){
    int i;
    for(i = 0; i < rows ; i++) {
        free(board[i]);
    }
    free(board);
}

int isFightCommand(char command){
    if (command == 'n'|| command == 'b'||command == 'p')
        return 1;
    else
       return 0;
}

char toLowercase(char command){
        return tolower(command);
}

int countOfAliveZombies(char **board){
        int count=0 , i, j;
        for (i = 0;i < rows ;i++){
                for (j = 0;j < cols ;j++){
                        if (isZombie(board[i][j]))
                                count++;
                }
        }
        return count;
}


int isZombie(char z){
        if(z>='1'&&z<='9')
                return 1;
        else 
                return 0;
}

int charToNumber(char ch){
        if (ch >= '0' && ch <= '9')
                return ch - '0'; 
        ch = toLowercase(ch);
        if (ch >= 'a' && ch <= 'z') {
                return (ch - 'a') + 10;
        }
        return -1;
}


void creationOfTheTestBoard(){
        int i,j;
        rows=7;
        cols=8;
        board = malloc((7)*sizeof(char*));
        if(board==NULL)
                printf("ERROR 1");
        for(i=0;i<rows;i++)
        {
                board[i]=malloc((cols)*sizeof(char*));
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
        
        for(i = 0; i < rows ; i++) {
            for(j = 0; j < cols ; j++) {
                board[i][j] = template[i][j];
            }
        }
        
        print(board);
}

void dramaticEndOfGame(char command){
        printf("\n================================================\n");
        printf("               END OF THE GAME\n");
        printf("===============================================\n");
        
        if (command == 'x') {
                printf("You chose to escape the fight... :( \n");
                printf("The zombies continue to run the entire earth.\n");
                printf("Humanity's last hope was YOU \n");
                printf("And now you fade into the FEARRr...\n");
        } else {
                printf("CONGRATULATIONS! You just eradicated the zombie outbreak!\n");
                printf("The hole planet are finally safe from the undead menace.\n");
                printf("Now humanity can return to normal, and safely proceed\n");
                printf("to destroy itself with World War III...\n");
                printf("        DAN DAN DAN...\n");
        }
        printf("--------------------------------------------------\n");
        printf("GAME INFO :\n");
        printf("Levels Completed  : %d\n", level - 1);
        printf("Final Score       : %d\n", score);
        printf("--------------------------------------------------\n");
}


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