#include <stdio.h>
#include <stdlib.h>
#include <string.h> //字符串标准函数库
int StringAdd(char *str);
char *StringCat(char *temp, char *str, char *astr);

//介绍对字符串的使用
int main()
{
    //指针不能给数组赋值，因为所占字节长度不同，转换过程中会造成数据丢失
    char hi[] = "I am happy";
    //数组的遍历和字符串的输出方式；
    //方式1,不建议使用
    for (int i = 0; i < strlen(hi); i++)
    {
        printf("%c", hi[i]);
    }
    printf("\n");
    //方式2
    printf(hi);
    printf("\n");
    //字符串形式（%s）的输出
    printf("%s\n", hi);

    //指针形式的字符串
    //对于printf和scanf最重要的是起始地址
    char *String = "ni hao";
    printf("指针字符串的输出\n");
    printf(String);
    printf("\n");
    printf("%s\n", String);
    //对于printf而言只要知道字符串的起始地址就能一直打印下去知道遇到\0为止。
    // printf("Hello \\0 world");

    //被连接的字符串只能是动态的数组声明的形式，若以指针形式因为分配的是静态内存，所以在
    //被连接时内存不会变大。
    char name[256] = "我能被连接吗？";
    char *Anothername = "我被连接进来了";

    //字符串的连接
    printf("字符串的连接  %s\n", strcat(name, Anothername));

    //字符串的复制,要注意的是被复制的字符串应有足够的大小
    printf("字符串的复制  %s\n", strcpy(name, Anothername));

    //字符串的比较,strcmp(),返回的是int型
    //若前面的字符串比后面的大则返回1，相等：0，小于：-1；
    //根据ascii值进行比对逐个字符进行比较即使字符串较短也有可能大于较长字符串
    printf("字符串的比较  %d\n", strcmp("helz", "hello"));

    //字符串长度的计算，函数strlen() 没有计算\0;
    printf("字符串长度的计算  %d\n", strlen("come  on"));

    //srpintf()的应用,相当于把要输入的字符串放入另一字符串中
    printf("name=%s\n", name);
    sprintf(name, "%s%s%s\n", name, "你好", "吗？");
    printf("name=%s", name);

    //自己写字符串长度计算
    printf("%d\n", StringAdd("nihao"));

    //自己写字符串的连接
    char *name1 = "my name is";
    char *name2 = "Li xing ze";
    //申请空间使得字符串能被放进指针中
    char *temp = (char *)malloc(strlen(name1) + strlen(name2) + 1);
    printf("%s\n", StringCat(temp, name1, name2));
    free(temp);

    // printf("字符的输出\n");
    // char character='a';
    // putchar(character);
    // puts("");
    // character=getchar();
    // putchar(character);

    return 0;
}
//对字符串的连接
char *StringCat(char *temp, char *str, char *astr)
{
    //记录起始地址值
    char *start = temp;
    while (*str)
    {
        *temp++ = *str++;
    }
    while (*astr)
    {
        *temp++ = *astr++;
    }
    *temp = '\0';
    return start;
}

int StringAdd(char *str)
{
    //方式一
    // int count=0;
    // while(*str){
    //     *str++;
    //     count++;
    // }
    // return count;

    //方式二,此方法是用末地址减去首地址
    char *temp = str;
    while (*str)
        str++;
    return str - temp;
}
