#include<stdio.h>

int hasNoMove(int next[8][8], int color, int check);
void printWinner();
void printChessBoard();
void makeMove(int x, int y, int color);
void getBestMove(int color);
void checkNewStepByColor(int next[8][8], int color);
void checkNewStep(int next[8][8], int x, int y, int color);
int newStep(int x, int y, int dx, int dy, int color);

int chess[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 2, 0, 0, 0},
    {0, 0, 0, 2, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

int directions[8][2] = { {-1, -1},{-1, 0},{-1, 1},{0, -1},{0, 1},{1, -1},{1, 0},{1, 1} };

int main() {
    int chess[8][8], next[8][8], color, x, y, check = 0;
    while (check < 2) {
        check = 0;
        int checktemp = check;
        check = hasNoMove(chess, 1, check);
        if (check == checktemp) {
            printf("1 黑棋你下\n");
            printChessBoard();
            checkNewStepByColor(next, 1);
            printf("請下合法的位置 x y\n");
            scanf("%d %d", &x, &y);
            makeMove(x, y, 1);
        }
        checktemp = check;
        check = hasNoMove(chess, 2, check);
        if (check == checktemp) {
            printf("2 白棋電腦下\n");
            printChessBoard();
            getBestMove(2);
        }
    }
    printWinner();

    return 0;
}


int hasNoMove(int next[8][8], int color, int check) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            next[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chess[i][j] == 0)
                checkNewStep(next, i, j, color);
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (next[i][j] == 1) {
                return check;
            }
        }
    }
    return check+1;
}

void printWinner() {
    int blackCount = 0, whiteCount = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chess[i][j] == 1) {
                blackCount++;
            }
            else if (chess[i][j] == 2) {
                whiteCount++;
            }
        }
    }

    if (blackCount > whiteCount) {
        printf("黑棋獲勝 %d : %d\n", blackCount, whiteCount);
    }
    else if (blackCount < whiteCount) {
        printf("白棋獲勝 %d : %d\n", whiteCount, blackCount);
    }
    else {
        printf("平局\n");
    }
}

void printChessBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d ", chess[i][j]);
        }
        printf("\n");
    }
}

void makeMove(int x, int y, int color) {
    chess[x][y] = color;
    for (int k = 0; k < 8; k++) {
        int dx = directions[k][0];
        int dy = directions[k][1];
        int flips = newStep(x, y, dx, dy, color);
        for (int i = 1; i <= flips; i++) {
            chess[x + i * dx][y + i * dy] = color;
        }
    }
}

void getBestMove(int color) {
    int max_x = -1;
    int max_y = -1;
    int max_flips = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chess[i][j] == 0) {
                int flips = 0;
                for (int k = 0; k < 8; k++) {
                    int dx = directions[k][0];
                    int dy = directions[k][1];
                    flips += newStep(i, j, dx, dy, color);
                }
                if (flips > max_flips) {
                    max_flips = flips;
                    max_x = i;
                    max_y = j;
                }
            }
        }
    }
    if (max_x != -1 && max_y != -1) {
        printf("電腦下 (%d,%d), 可翻轉 %d 子\n", max_x, max_y, max_flips);
        makeMove(max_x, max_y, color);
    }
}


void checkNewStepByColor(int next[8][8], int color)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            next[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(chess[i][j] == 0)
            checkNewStep(next, i, j, color);
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (next[i][j] > 0) {
                printf("(%d,%d) ", i, j);
            }
        }
    }
    printf("\n");
}


void checkNewStep(int next[8][8], int x, int y, int color) {
    for (int k = 0; k < 8; k++) {
        int dx = directions[k][0];
        int dy = directions[k][1];
        int n = newStep(x, y, dx, dy, color);
        if (n > 0) {
            next[x][y] = 1;
        }
    }
}

int newStep(int x, int y, int dx, int dy, int color)
{
    int X = x + dx;
    int Y = y + dy;
    int n = 1;

    if (X >= 0 && X < 8 && Y >= 0 && Y < 8) {
        if (chess[X][Y] != color && chess[X][Y] != 0) {
            while (X >= 0 && X < 8 && Y >= 0 && Y < 8) {
                if (chess[X][Y] == 0) {
                    break;
                }
                else if (chess[X][Y] == color) {
                    return n;
                }
                X += dx;
                Y += dy;
                n++;
            }
        }
    }
    return 0;
}
