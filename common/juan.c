#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
char keywords[30][12] = {"program", "begin", "end", "var", "while", "do", "repeat",
                         "until", "for", "to", "if", "then", "else", ";", ":", "(", ")", ",",
                         ":=", "+", "-", "*", "/", ">", ">=", "==", "<", "<="};
int num_key = 28;
int aut[11][8] = {0, 0, 0, 0, 0, 0, 0, 0,
                  0, 2, 0, 0, 0, 8, 9, 15,
                  0, 2, 3, 5, 11, 0, 0, 11,
                  0, 4, 0, 0, 0, 0, 0, 0,
                  0, 4, 0, 5, 11, 0, 0, 11,
                  0, 7, 0, 0, 6, 0, 0, 0,
                  0, 7, 0, 0, 0, 0, 0, 0,
                  0, 7, 0, 0, 11, 0, 0, 11,
                  0, 8, 0, 0, 0, 8, 0, 12,
                  0, 0, 0, 0, 0, 0, 10, 14,
                  0, 0, 0, 0, 0, 0, 0, 13};
char ID[50][12];
int C[20];
int num_ID = 0, num_C = 0;

struct token
{
    int code;
    int value;
};                              //Token结构
struct token tok[100];          //Token数组
int i_token = 0, num_token = 0; //Token计数器和Token个数
char strTOKEN[15];              //当前单词
int i_str;                      //当前单词指针
int n, p, m, e, t;              //尾数值，指数值，小数位数，指数符号，类型
double num;                     //常数值
char w[50];                     //源程序缓冲区
int i;                          //源程序缓冲区指针,当前字符为w[i]

struct map //当前字符到状态转换矩阵列标记的映射
{
    char str[50];
    int col;
};
struct map col1[4] = {{"0123456789", 1}, {".", 2}, {"Ee", 3}, {"+-", 4}};    //数字
struct map col2[2] = {{"abcdefghijklmnopqrstuvwxyz", 5}, {"0123456789", 1}}; //关键字或标识符
struct map col3[1] = {{";:(),+-*/=><", 6}};                                  //界符
struct map *ptr;
int num_map;

void act(int s);
int find(int s, char ch);
int InsertConst(double num);
int Reserve(char *str);
int InsertID(char *str);

int main(int argc, char *argv[])
{
    FILE *fp;
    int s; //当前状态
    fp = fopen("exa.txt", "r");
    if (fp==NULL)
    {
        printf("文件读取错误");
        return 0;
    }
    while (!feof(fp))
    {
        fgets(w, 50, fp);
        i = 0;
        do
        {
            while (w[i] == ' ') //滤空格
                i++;

            if (w[i] >= 'a' && w[i] <= 'z') //判定单词类别
            {
                ptr = col2;
                num_map = 2;
            }
            else if (w[i] >= '0' && w[i] <= '9')
            {
                ptr = col1;
                num_map = 4;
            }
            else if (strchr(col3[0].str, w[i]) == NULL)
            {
                printf("非法字符%c\n", w[i]);
                i++;
                continue;
            }
            else
            {
                ptr = col3;
                num_map = 1;
            }

            i--;
            s = 1; //开始处理一个单词
            while (s != 0)
            {
                act(s);
                if (s >= 11 && s <= 14)
                    break;
                i++; //getchar()
                s = find(s, w[i]);
            }
            if (s == 0)
            {
                strTOKEN[i_str] = '\0';
                printf("词法错误：%s\n", strTOKEN);
            }

        } while (w[i] != 10);
    }

    printf("关键字表："); //输出结果
    for (i = 0; i < 30; i++)
        printf("%s ", keywords[i]);
    printf("\n");
    printf("Token序列：");
    for (i = 0; i < num_token; i++)
        printf("(%d,%d)", tok[i].code, tok[i].value);
    printf("\n");
    printf("符号表：");
    for (i = 0; i < num_ID; i++)
        printf("%s ", ID[i]);
    printf("\n");
    printf("常数表：");
    for (i = 0; i < num_C; i++)
        printf("%d ", C[i]);
    printf("\n");

    fclose(fp);
    printf("Hello World!\n");
    return 0;
}

void act(int s)
{
    int code;
    switch (s)
    {
    case 1:
        n = 0;
        m = 0;
        p = 0;
        t = 0;
        e = 1;
        num = 0;
        i_str = 0;
        strTOKEN[i_str] = '\0'; //其它变量初始化
        break;
    case 2:
        n = 10 * n + w[i] - 48;
        break;
    case 3:
        t = 1;
        break;
    case 4:
        n = 10 * n + w[i] - 48;
        m++;
        break;
    case 5:
        t = 1;
        break;
    case 6:
        if (w[i] == '-')
            e = -1;
        break;
    case 7:
        p = 10 * p + w[i] - 48;
        break;
    case 8:
        strTOKEN[i_str++] = w[i]; //将ch中的符号拼接到strTOKEN的尾部；
        break;
    case 9:
        strTOKEN[i_str++] = w[i]; //将ch中的符号拼接到strTOKEN的尾部；
        break;
    case 10:
        strTOKEN[i_str++] = w[i]; //将ch中的符号拼接到strTOKEN的尾部；
        break;
    case 11:
        num = n * pow(10, e * p - m); //计算常数值
        tok[i_token].code = 2;
        tok[i_token++].value = InsertConst(num); //生成常数Token
        num_token++;
        break;
    case 12:
        strTOKEN[i_str] = '\0';
        code = Reserve(strTOKEN); //查关键字表
        if (code)
        {
            tok[i_token].code = code;
            tok[i_token++].value = 0;
        } //生成关键字Token
        else
        {
            tok[i_token].code = 1;
            tok[i_token++].value = InsertID(strTOKEN);
        } //生成标识符Token
        num_token++;
        break;
    case 13:
        strTOKEN[i_str] = '\0';
        code = Reserve(strTOKEN); //查界符表
        if (code)
        {
            tok[i_token].code = code;
            tok[i_token++].value = 0;
        } //生成界符Token
        else
        {
            strTOKEN[strlen(strTOKEN) - 1] = '\0'; //单界符
            i--;
            code = Reserve(strTOKEN); //查界符表
            tok[i_token].code = code;
            tok[i_token++].value = 0; //生成界符Token
        }
        num_token++;
        break;
    case 14:
        strTOKEN[i_str] = '\0';
        code = Reserve(strTOKEN); //查界符表
        tok[i_token].code = code;
        tok[i_token++].value = 0; //生成界符Token
        num_token++;
        break;
    }
}
int find(int s, char ch)
{
    int i, col = 7;
    struct map *p;
    p = ptr;
    for (i = 0; i < num_map; i++)
        if (strchr((p + i)->str, ch))
        {
            col = (p + i)->col;
            break;
        }
    return aut[s][col];
}
int InsertConst(double num)
{
    int i;
    for (i = 0; i < num_C; i++)
        if (num == C[i])
            return i;
    C[i] = num;
    num_C++;
    return i;
}

int Reserve(char *str)
{
    int i;
    for (i = 0; i < num_key; i++)
        if (!strcmp(keywords[i], str))
            return (i + 3);
    return 0;
}

int InsertID(char *str)
{
    int i;
    for (i = 0; i < num_ID; i++)
        if (!strcmp(ID[i], str))
            return i;
    strcpy(ID[i], str);
    num_ID++;
    return i;
}
