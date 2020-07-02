#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

// メモリの確保
char **initBoard(int size);

// ボード生成
void createBoard(char **board, int size, int bombCount);

// ランダムな整数の生成
int randint(int min, int max);

// Mの配置
void bombSetup(char **board, int size, int bombCount);

// 周りのMのカウント
void aroundBombCount(char **board, int size);

// ボードの表示
void displayBoard(char **board, int size);

// ゲームの進行
int play(char **backBoard, char **showBoard, int size, int bombCount);

// 入力値のチェック
int checkInput(int x, int y, int mode, int size);

// マスのオープン
void openSquare(char **backBoard, char **showBoard, int x, int y);

// マスにマーク
void checkSquare(char **showBoard, int x, int y);

// 入力値の重複判定
int duplicatedInput(char **backboard, char **showBoard, int x, int y);

// 結果の表示
void displayResult(int isCompleted, int gameTime);

int main() {
    char **backBoard;
    char **showBoard;
    int size;
    int bombCount;
    int isCompleted;
    int gameTime;
    time_t start,end;

    srand((unsigned int) time(NULL));

    printf("ボードサイズ > ");
    scanf("%d", &size);
    printf("Mの数 > ");
    scanf("%d", &bombCount);

    // Mの数が適切かチェック
    if (bombCount > size * 2 - 1){
        printf("ボードのマスよりMの数が多くなっています．");
        exit(0);
    }

    // ボード生成
    backBoard = initBoard(size);
    showBoard = initBoard(size);
    createBoard(backBoard, size, bombCount);

    // ゲームプレイ
    start = time(NULL);
    isCompleted = play(backBoard, showBoard, size, bombCount);
    end = time(NULL);
    gameTime = (int)(end-start);

    // 結果表示
    displayResult(isCompleted,gameTime);


    return 0;
}

char **initBoard(int size) {
    // メモリの確保
    char **board;
    board = malloc(sizeof(char *) * size);
    for (int i = 0; i < size; ++i) {
        board[i] = malloc(sizeof(char) * size);
    }

    // 全て”.”で初期化
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
    // 指定された範囲のランダムな整数の生成
    return min + (int) (rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

void bombSetup(char **board, int size, int bombCount) {
    int x, y;
    int i = 0;
    while (i < bombCount) {
        x = randint(0, size - 1);
        y = randint(0, size - 1);

        // 重複判定
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
            // Mが配置されていないマスをチェック
            if (board[i][j] != 'M') {
                // 周りを1マスずつチェック
                for (int k = i - 1; k <= i + 1; ++k) {
                    for (int l = j - 1; l <= j + 1; ++l) {
                        // チェックするマスがボード上に存在するか
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


int play(char **backBoard, char **showBoard, int size, int bombCount) {
    int x, y, mode;
    int openCount = 0;
    int isCompleted = FALSE;
    displayBoard(showBoard, size);
    while (!isCompleted) {
        printf("x y mode > ");
        scanf("%d %d %d", &x, &y, &mode);

        // 入力チェック
        if (checkInput(x, y, mode, size)) {
            printf("座標またはモードの指定が間違っています．x座標 y座標 モード(0:オープン，1:マーク)の順にもう一度入力してください．\n");
            continue;
        }

        //  重複チェック
        if (duplicatedInput(backBoard, showBoard, x, y)) {
            printf("すでにそのマスはオープンしています．\n");
            continue;
        }

        if (mode == 0) {
            // マスをオープン
            openSquare(backBoard, showBoard, x, y);
            // Mのマスをオープンした場合は終了
            if (showBoard[y][x] == 'M') {
                displayBoard(showBoard, size);
                break;
            }
            openCount++;
        } else {
            // マスに"?"をマークする
            checkSquare(showBoard, x, y);
        }

        // クリア判定
        if (openCount == size * 2 - bombCount) {
            isCompleted = TRUE;
        }
        displayBoard(showBoard, size);
    }

    return isCompleted;
}

void displayBoard(char **board, int size) {
    printf("\n  ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < size; ++i) {
        printf("%d ", i);
        for (int j = 0; j < size; ++j) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int checkInput(int x, int y, int mode, int size) {
    // 指定された値が範囲外ではないかモードは適切か
    if ((0 <= x && x < size) && (0 <= y && y < size) && (mode == 0 || mode == 1)) {
        return FALSE;
    } else {
        return TRUE;
    }
}

void openSquare(char **backBoard, char **showBoard, int x, int y) {
    showBoard[y][x] = backBoard[y][x];
}

void checkSquare(char **showBoard, int x, int y) {
    showBoard[y][x] = '?';
}

int duplicatedInput(char **backboard, char **showBoard, int x, int y) {
    if (backboard[y][x] == showBoard[y][x]) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void displayResult(int isCompleted,int gameTime){
    if (isCompleted){
        printf("ゲームクリア！\n");
    } else {
        printf("ゲームオーバー！\n");
    }
    printf("記録:%d秒",gameTime);
}