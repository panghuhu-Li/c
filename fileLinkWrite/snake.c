#include "snake.h"

void initSnake(snake* head) {
    int i;
    snake* tail;
    //以snake结构体的形式开辟一块新的内存，内存中的数据是新的，用tail指向这个结构体
    tail = (snake*)malloc(sizeof(snake));
    if (tail == NULL) {
        perror("tail malloc failed");
    }
    tail->x = 30;
    tail->y = 30;
    tail->next = NULL;
    for (i = 0; i < 4; i++) {
        head = (snake*)malloc(sizeof(snake));
        head->x = 30 + i;  //下一节点的位置
        head->y = 30;
        head->next = tail;  //链接成链
        tail = head;        //将尾指针传向下一个头指针
    }
}