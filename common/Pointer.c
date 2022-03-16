#include<stdio.h>

int main(){
    //在64位中指针占8个字节
    //在定义的时候 *只能说明ptr是指针变量而不是普通变量
    int *ptr=NULL;
    int number=100;
    ptr=&number;
    //在使用时*ptr表示ptr保存的地址编号所对应空间中的内容
    printf("%d\n",*ptr);
    //指针变量的两种类型：自身的类型和所指向的类型
    //自身类型：在定义时将自身变量去掉剩下的部分为自身类型 int *
    //所指向的类型：去掉变量名称和离其最近的*剩下的部分为其所指向的类型 int
    //所指向类型的作用：决定了指针变量所取空间内容的宽度以及指针变量+1所跳过的单位跨度
    printf("&number=%u\n",&number);
    printf("ptr=%u\n",ptr);
    printf("ptr+1=%u\n",ptr+1);
    return 0;
}