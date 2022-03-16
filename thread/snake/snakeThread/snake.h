#ifndef SNAKE_H_
#define SNAKE_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    Snake* snake;
    struct SNAKELIST* next;
} SnakeList;

typedef struct arguments {
    SnakeList* snakeListHead;
    Food* food;
} Arguments;

Food food;
SnakeList* snakeList;

int timeU = 500000;
int kx = 0;
int ky = 0;

char key;

void initFood() {
    srand(time(NULL));
    food.X = rand() % 76 + 2;  // 2-78
    food.Y = rand() % 26 + 2;  // 2-28
}

void initSnake(Snake* snake) {
    int x = rand() % 45 + 5;
    int y = rand() % 24 + 3;

    snake->body[0].X = x;
    snake->body[0].Y = y; /*蛇头*/
    snake->body[1].X = x - 1;
    snake->body[1].Y = y; /*蛇尾*/
    snake->size = 2;
}

void setUI(void);

void showGame() {
    // fprintf(stdout, "\033[1;1H");
    // fflush(stdout);
    // system("clear");
    // SnakeList* snakeListHead, Food* food
    // Arguments* arguments = (Arguments*)arg;
    // SnakeList* snakeListHead = arguments->snakeListHead;
    // Food* food = arguments->food;

    int screen[HIGH][WIDE] = {0};

    //食物
    screen[food.Y][food.X] = 10;

    SnakeList* current = snakeList->next;
    while (current) {
        Snake* snake = current->snake;
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

void gameEnd(void) {
    pthread_exit(0);
}

void* getInput(void* message) {
    key = 'd';
    while (1) {
        int keytmp = fgetc(stdin);
        if (key != keytmp) {
            key = keytmp;
        }
        if (key == 'q') {
            gameEnd();
            break;
        }
    }
}

void playGame(void) {
    SnakeList* current = snakeList->next;
    if (current != NULL) {
        Snake* snake = current->snake;

        while (snake->size < (HIGH - 1) * (WIDE - 1)) {
            switch (key) {
                case 'w':
                    kx = 0;
                    ky = -1;
                    break;
                case 'a':
                    kx = -1;
                    ky = 0;
                    break;
                case 's':
                    kx = 0;
                    ky = 1;
                    break;
                case 'd':
                    kx = 1;
                    ky = 0;
                    break;
                default:
                    break;
            }
            int i;
            //判断是否撞墙
            if (snake->body[0].X == 0 || snake->body[0].X == WIDE - 1 ||
                snake->body[0].Y == 0 || snake->body[0].Y == HIGH - 1) {
                gameEnd();
            }
            //判断是否撞到蛇身
            for (i = 1; i < snake->size; i++) {
                if (snake->body[0].X == snake->body[i].X &&
                    snake->body[0].Y == snake->body[i].Y) {
                    gameEnd();
                }
            }
            //判断是否撞到食物
            if (snake->body[0].X == food.X && snake->body[0].Y == food.Y) {
                initFood();
                snake->size++;
                if (timeU >= 200000) {
                    timeU -= 50000;
                }
            }

            for (i = snake->size - 1; i > 0; i--) {
                snake->body[i].X = snake->body[i - 1].X;
                snake->body[i].Y = snake->body[i - 1].Y;
            }
            snake->body[0].X = snake->body[0].X + kx;
            snake->body[0].Y = snake->body[0].Y + ky;
            showGame();
            usleep(500000);
        }
    }
}

void SnakeListAdd(SnakeList* snakeListHead, int snakeUid, Snake* snake) {
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