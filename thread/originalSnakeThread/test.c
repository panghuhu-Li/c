#include "snake.h"

static char key;
int main() {
    pthread_t t1;
    pthread_create(&t1, NULL, getInput, NULL);
    setUI();
    srand(time(NULL));
    initFood();
    initSnake();
    playGame();
    // getInput();
    return 0;
}
void initFood(void) {
    food.X = rand() % 76 + 2;  // 2-78
    food.Y = rand() % 26 + 2;  // 2-28
}
void initSnake(void) {
    snake.body[0].X = 40;
    snake.body[0].Y = 15; /*蛇头*/
    snake.body[1].X = 39;
    snake.body[1].Y = 15; /*蛇尾*/
    snake.size = 2;
}
void setUI(void) {
    /* 屏幕设置 */
    // printf("\033[2J");             // 清屏
    system("clear");
    system("stty -icanon");        // 关缓冲
    system("stty -echo");          // 关回显
    // fprintf(stdout, "\033[?25l");  // 关闭鼠标显示
}
void showGame(void) {
    // fprintf(stdout, "\033[1;1H");
    // fflush(stdout);
    system("clear");

    int screen[HIGH][WIDE] = {0};

    //食物
    screen[food.Y][food.X] = 10;
    //蛇头
    screen[snake.body[0].Y][snake.body[0].X] = 9;
    //蛇尾
    int i, k, j;
    for (k = 1; k < snake.size; k++) {
        screen[snake.body[k].Y][snake.body[k].X] = 8;
    }
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
    while (snake.size < (HIGH - 1) * (WIDE - 1)) {
        showGame();
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
        if (snake.body[0].X == 0 || snake.body[0].X == WIDE - 1 ||
            snake.body[0].Y == 0 || snake.body[0].Y == HIGH - 1) {
            gameEnd();
        }
        //判断是否撞到蛇身
        for (i = 1; i < snake.size; i++) {
            if (snake.body[0].X == snake.body[i].X &&
                snake.body[0].Y == snake.body[i].Y) {
                gameEnd();
            }
        }
        //判断是否撞到食物
        if (snake.body[0].X == food.X && snake.body[0].Y == food.Y) {
            initFood();
            snake.size++;
            if (timeU >= 200000) {
                timeU -= 50000;
            }
        }

        for (i = snake.size - 1; i > 0; i--) {
            snake.body[i].X = snake.body[i - 1].X;
            snake.body[i].Y = snake.body[i - 1].Y;
        }
        snake.body[0].X = snake.body[0].X + kx;
        snake.body[0].Y = snake.body[0].Y + ky;
        showGame();
        usleep(timeU);
    }
}
void gameEnd(void) {
    /* 恢复终端设置 */
    system("stty icanon");         // 恢复缓冲
    system("stty echo");           // 恢复回显
    fprintf(stdout, "\033[?25h");  // 恢复鼠标显示

    /* 尾部处理 */
    fprintf(stdout, "\033[200;1H");  // 定位光标到最后一行
    exit(0);                         // 退出程序
}