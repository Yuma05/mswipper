#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

char **initBoard(int size);

void createBoard(char **board, int size, int bombCount);

int randint(int min, int max);

void bombSetup(char **board, int size, int bombCount);

void aroundBombCount(char **board, int size);

void displayBoard(char **board, int size);

void play(char **backBoard ,char **showBoard,int size,int bomb);

int checkInput(int x,int y, int mode,int size);

void openSquare(char **backBoard,char **showBoard,int x,int y);

void checkSquare(char **showBoard,int x,int y);

int main() {
    srand((unsigned int) time(NULL));
    char **backBoard;
    char **showBoard;
    int size;
    int bomb;
    printf("ボードサイズ > ");
    scanf("%d", &size);
    printf("Mの数 > ");
    scanf("%d", &bomb);
    backBoard = initBoard(size);
    showBoard = initBoard(size);

    createBoard(backBoard, size, bomb);
    play(backBoard,showBoard,size,bomb);


    return 0;
}

char **initBoard(int size) {
    char **board;
    board = malloc(sizeof(char *) * size);
    for (int i = 0; i < size; ++i) {
        board[i] = malloc(sizeof(char) * size);
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = '.';
        }
    }
    return board;
}

void createBoard(char **board, int size, int bombCount) {
    bombSetup(board, size, bombCount);
    aroundBombCount(board, size);
    displayBoard(board, size);
}

int randint(int min, int max) {
    return min + (int) (rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

void bombSetup(char **board, int size, int bombCount) {
    int x, y;
    int i = 0;
    while (i < bombCount) {
        x = randint(0, size - 1);
        y = randint(0, size - 1);
        if (board[y][x] != 'M') {
            board[y][x] = 'M';
            i++;
        }
    }
}

void aroundBombCount(char **board, int size) {
    int aroundBombCount = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] != 'M') {
                for (int k = i - 1; k <= i + 1; ++k) {
                    for (int l = j - 1; l <= j + 1; ++l) {
                        if (0 <= k && k < size && 0 <= l && l < size) {
                            if (board[k][l] == 'M') {
                                aroundBombCount++;
                            }
                        }
                    }
                }
                board[i][j] = aroundBombCount + '0';
                aroundBombCount = 0;
            }
        }
    }
}


void play(char **backBoard ,char **showBoard,int size,int bomb){
    int x,y,mode;
    int openCount = 0;
    int isCompleted = FALSE;
    displayBoard(showBoard, size);
    while (!isCompleted) {
        printf("x y mode");
        scanf("%d %d %d", &x,&y,&mode);
        if(checkInput(x,y,mode,size) != TRUE){
            printf("不正な値です．もう一度入力してください．");
            continue;
        }


        if (mode == 0){
            openSquare(backBoard,showBoard,x,y);
            openCount++;
        } else {
            checkSquare(showBoard,x,y);
        }

        if (openCount == size*2 - bomb){
            int isCompleted = TRUE;
        }

        displayBoard(showBoard,size);
    }
}

void displayBoard(char **board, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

int checkInput(int x,int y, int mode,int size){
    if ((0 <= x && x < size) && (0 <= y && y < size) && (mode == 0 || mode == 1)){
        return TRUE;
    } else {
        return FALSE;
    }
}

void openSquare(char **backBoard,char **showBoard,int x,int y){
    showBoard[y][x] = backBoard[y][x];
}

void checkSquare(char **showBoard,int x,int y){
    showBoard[y][x] = '?';
}