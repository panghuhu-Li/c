

#ifndef _SNAKE_H
#define _SNAKE_H

int Init_map(char** map, int N);  //沙盘初始化函数,实现边缘，以及随机食物位置

void map_printf(char** map,
                int N);  //打印地图，参数一表示地图，参数二表示地图大小
int snake_move(
    char** map,
    int N,
    char** snake,
    int* M,
    char
        away);  // m是蛇的长度，默认snake是两列的,away是目前snake应该前进的方向，默认不能为空；

#endif
