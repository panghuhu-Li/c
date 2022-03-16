#ifndef SNAKE_H_
#define SNAKE_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDE 80
#define HIGH 30

typedef struct FOOD {
    int X;
    int Y;
} Food;

typedef struct BODY {
    int X;
    int Y;
} Body;

typedef struct SNAKE {
    struct BODY body[HIGH * WIDE];
    int size;
} Snake;

typedef struct SNAKELIST {
    int snakeUid;
    Snake *snake;
    struct SNAKELIST* next;
} SnakeList;

int timeU = 500000;
int kx = 0;
int ky = 0;

void initFood(Food* food) {
    food->X = rand() % 76 + 2;  // 2-78
    food->Y = rand() % 26 + 2;  // 2-28
}

void initSnake(Snake* snake) {

    int x=rand() % 45 + 5;
    int y=rand() % 24 + 3;
    
    snake->body[0].X = x;
    snake->body[0].Y = y; /*蛇头*/
    snake->body[1].X = x-1;
    snake->body[1].Y = y; /*蛇尾*/
    snake->size = 2;
}

void setUI(void);

void showGame(SnakeList* snakeListHead, Food* food) {
    // fprintf(stdout, "\033[1;1H");
    // fflush(stdout);
    // system("clear");

    int screen[HIGH][WIDE] = {0};

    //食物
    screen[food->Y][food->X] = 10;

    SnakeList* current = snakeListHead->next;
    while (current) {
        Snake *snake = current->snake;
        //蛇头
        screen[snake->body[0].Y][snake->body[0].X] = 9;
        //蛇尾
        int k;
        for (k = 1; k < snake->size; k++) {
            screen[snake->body[k].Y][snake->body[k].X] = 8;
        }
        current = current->next;
    }

    int i, j;
    //画墙
    for (i = 0; i < HIGH; i++) {
        for (j = 0; j < WIDE; j++) {
            screen[0][j] = 7;  //横线
            screen[HIGH - 1][j] = 7;
            screen[i][0] = 6;  //竖线
            screen[i][WIDE - 1] = 6;
        }
    }

    for (i = 0; i < HIGH; i++) {
        for (j = 0; j < WIDE; j++) {
            if (screen[i][j] == 10) {
                fprintf(stdout, "#");
            }
            if (screen[i][j] == 9) {
                fprintf(stdout, "@");
            }
            if (screen[i][j] == 8) {
                fprintf(stdout, "*");
            }
            if (screen[i][j] == 7) {
                fprintf(stdout, "_");
            }
            if (screen[i][j] == 6) {
                fprintf(stdout, "|");
            }
            if (screen[i][j] == 0) {
                fprintf(stdout, " ");
            }
        }
        fprintf(stdout, "\n");
    }
}

void* getInput(void* message);

void playGame(void);

void gameEnd(void);

void SnakeListAdd(SnakeList* snakeListHead, int snakeUid, Snake *snake) {
    SnakeList* node = (SnakeList*)malloc(sizeof(SnakeList));
    if (node == NULL) {
        perror("SnakeList add malloc failed\n");
        exit(1);
    }
    node->snakeUid = snakeUid;
    node->snake = snake;
    /*采用头插法*/
    node->next = snakeListHead->next;
    snakeListHead->next = node;
}

void SnakeListRm(SnakeList* snakeListHead, int snakeUid) {
    SnakeList* pre = snakeListHead;
    SnakeList* current = snakeListHead->next;
    while (current) {
        if (current->snakeUid == snakeUid) {
            pre->next = current->next;
            free(current);
            break;
        }
        pre->next = current;
        current = current->next;
    }
}

#endif