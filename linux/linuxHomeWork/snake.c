
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "snake.h"

int Init_map(char** map, int N)  //沙盘初始化函数,实现边缘，以及随机食物位置
{
    int i = 0;
    for (i = 0; i < N; i++)  //边缘设为1
    {
        *((char*)map + i) = 1;
        *((char*)map + N * 15 + i) = 1;

        *((char*)map + N * i) = 1;
        *((char*)map + N * i + 15) = 1;
    }
    srand(time(NULL));  //调用随机数生成食物的位子
    for (i = 0; i < 10; i++) {
        *((char*)map + N * (rand() % 14 + 1) + (rand() % 14 + 1)) = 2;
    }
    return 0;
}

void map_printf(char** map,
                int N)  //打印地图，参数一表示地图，参数二表示地图大小
{
    int i = 0;
    int j = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf(" %d ", *((char*)map + N * i + j));
        }
        printf("\n");
    }
}

int snake_move(char** map, int N, char** snake, int* M, char away) {
    //*((char*)map +N**((char *)snake ) + *((char *)snake + 1))  = 3;

    int i = 0;
    int changei = 0, changej = 0;
    if (away == 'a') {
        changei = 0;
        changej = -1;
    } else if (away == 'd') {
        changei = 0;
        changej = 1;
    } else if (away == 'w') {
        changei = -1;
        changej = 0;
    } else if (away == 's') {
        changei = 1;
        changej = 0;
    }
    //优先判断snake下一步是什么
    if (*((char*)map + N * (*((char*)snake + 2 * 0 + 0) + changei) +
          *((char*)snake + 2 * 0 + 1) + changej) == 0)  // 0为空位
    {
        for (i = 0; i < *M; i++)  //打印当前snake的状态到地图上
        {
            *((char*)map + N * (*((char*)snake + 2 * i + 0)) +
              *((char*)snake + 2 * i + 1)) = 3;
        }
        //改变snake头部以及尾部在地图上的位置

        *((char*)map + N * (*((char*)snake + 2 * 0 + 0) + changei) +
          *((char*)snake + 2 * 0 + 1) + changej) = 3;

        *((char*)map + N * (*((char*)snake + 2 * (*M - 1) + 0)) +
          *((char*)snake + 2 * (*M - 1) + 1)) = 0;
        //改变snake数组蛇身的位置；
        for (i = (*M - 1); i > 0; i--) {
            *((char*)snake + 2 * i + 0) = *((char*)snake + 2 * (i - 1) + 0);
            *((char*)snake + 2 * i + 1) = *((char*)snake + 2 * (i - 1) + 1);
        }
        *((char*)snake + 2 * 0 + 1) = *((char*)snake + 2 * 0 + 1) + changej;
        *((char*)snake + 2 * 0 + 0) = *((char*)snake + 2 * 0 + 0) + changei;

        return 0;
    } else if (*((char*)map + N * (*((char*)snake + 2 * 0 + 0) + changei) +
                 *((char*)snake + 2 * 0 + 1) + changej) == 2)  // 0为空位
    {
        for (i = 0; i < *M; i++)  //打印当前snake的状态到地图上
        {
            *((char*)map + N * (*((char*)snake + 2 * i + 0)) +
              *((char*)snake + 2 * i + 1)) = 3;
        }
        //改变snake头部在地图上的位置

        *((char*)map + N * (*((char*)snake + 2 * 0 + 0) + changei) +
          *((char*)snake + 2 * 0 + 1) + changej) = 3;

        //改变snake数组蛇身的位置；
        for (i = *M; i > 0; i--) {
            *((char*)snake + 2 * i + 0) = *((char*)snake + 2 * (i - 1) + 0);
            *((char*)snake + 2 * i + 1) = *((char*)snake + 2 * (i - 1) + 1);
        }
        *((char*)snake + 2 * 0 + 1) = *((char*)snake + 2 * 0 + 1) + changej;
        *((char*)snake + 2 * 0 + 0) = *((char*)snake + 2 * 0 + 0) + changei;
        *M += 1;
        return 1;
    } else {
        return -1;
    }
    return 0;
}
