#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char **initBoard(int size);

void createBoard(char **board, int size, int bombCount);

int randint(int min, int max);

void bombSetup(char **board, int size, int bombCount);

void aroundBombCount(char **board, int size);

void showBoard(char **board, int size);

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
    showBoard(board, size);
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
        if (board[x][y] != 'M') {
            board[x][y] = 'M';
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

void showBoard(char **board, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}