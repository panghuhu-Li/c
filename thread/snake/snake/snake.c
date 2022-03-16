#include "snake.h"

int main() {
    SnakeList* snakeList;
    snakeList = (SnakeList*)malloc(sizeof(SnakeList));
    if (snakeList == NULL) {
        perror("snakeList malloc failed\n");
        exit(1);
    }
    snakeList->next = NULL;
    Snake* snake;
    snake = (Snake*)malloc(sizeof(Snake));
    if (snake == NULL) {
        perror("ini snake failed\n");
        exit(0);
    }
    initSnake(snake);
    SnakeListAdd(snakeList, 1, snake);
    Snake* snake2;
    snake2 = (Snake*)malloc(sizeof(Snake));
    initSnake(snake2);
    SnakeListAdd(snakeList, 2, snake2);
    Food* food;
    food = (Food*)malloc(sizeof(Food));
    if (food == NULL) {
        perror("ini Food error");
    }
    initFood(food);
    showGame(snakeList, food);
    SnakeListRm(snakeList,2);
    showGame(snakeList,food);
}