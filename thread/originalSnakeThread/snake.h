#ifndef SNAKE_H_
#define SNAKE_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDE 80
#define HIGH 30

struct FOOD {
    int X;
    int Y;
} food;

struct BODY {
    int X;
    int Y;
};

struct SNAKE {
    struct BODY body[HIGH * WIDE];
    int size;
} snake;

int timeU = 500000;
int kx = 0;
int ky = 0;
void initFood(void);
void initSnake(void);
void setUI(void);
void showGame(void);
void *getInput(void *message);
void playGame(void);
void gameEnd(void);
#endif /* SNAKE_H_ */
