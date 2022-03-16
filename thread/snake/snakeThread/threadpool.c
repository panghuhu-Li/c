#include "threadpool.h"
#include "snake.h"

void* process(void* arg) {
    printf("thread 0x%x working on task %d\n ", (unsigned int)pthread_self(),
           *(int*)arg);
    int i;
    for (i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    // sleep(1);
    printf("task %d is end\n", *(int*)arg);

    return NULL;
}

int main(void) {
    /*threadpool_t *threadpool_create(int min_thr_num, int max_thr_num, int
     * queue_max_size);*/

    /*创建线程池，池里最小3个线程，最大100，队列最大100*/
    threadpool_t* thp = threadpool_create(3, 100, 100);
    printf("pool initialized\n");

    snakeList = (SnakeList*)malloc(sizeof(SnakeList));
    snakeList->next = NULL;
    //创建第一条蛇
    Snake* snake;
    snake = (Snake*)malloc(sizeof(Snake));
    initSnake(snake);
    SnakeListAdd(snakeList, 1, snake);

    // Snake* snake2;
    // snake2 = (Snake*)malloc(sizeof(Snake));
    // initSnake(snake2);
    // SnakeListAdd(snakeList, 2, snake2);

    initFood();

    threadpool_add(thp, getInput, NULL);
    playGame();

    // Arguments arguments;
    // arguments.food = food;
    // arguments.snakeListHead = snakeList;

    // int number=100;
    // threadpool_add(thp, process, (void *)&number);
    sleep(1); /* 等子线程完成任务 */
    threadpool_destroy(thp);

    return 0;
}
