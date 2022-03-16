#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct snakeList {
    int x;
    int y;
    struct snakeList* next;
} snake;

void initSnake(snake* head);

#endif
