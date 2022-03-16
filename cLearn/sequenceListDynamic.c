#include <stdio.h>
#include <stdlib.h>

//顺序表静态分配的最大存储空间
#define maxSize 50
/**
 * @brief 动态分配顺序表结构体
 * length表示当前长度,其中length表示当前插入位置
 */
typedef struct list {
    int* date;
    int length;
} SqList;

/**
 * @brief 初始化顺序表
 *
 * @param l
 * @return int 初始化成功返回1，失败返回0
 */
int InitList(SqList* l) {
    l = (SqList*)malloc(sizeof(int) * maxSize);
    l->length = 0;
}

/**
 * @brief 顺序表的插入
 *
 * @param l 顺序表
 * @param index 插入的位置下标
 * @param element 插入的元素
 * @return int 成功返回1 失败返回0
 */
int ListInsert(SqList* l, int index, int element) {
    //判断插入位置是否合法
    if (index < 1 || index > l->length + 1) {
        printf("the index you want to insert exceed the range\n");
        return 0;
    }
    //数组已满无法插入
    if (l->length >= maxSize) {
        printf("the list has full\n");
        return 0;
    }

    for (int j = l->length; j >= index; j--) {
        l->date[j] = l->date[j - 1];
    }

    l->date[index - 1] = element;
    l->length++;
    return 1;
}

/**
 * @brief 顺序表的删除
 *
 * @param l 顺序表
 * @param index 删除的下标
 * @param element 删除的元素
 * @return int 成功返回1 失败返回0
 */
int ListDelete(SqList* l, int index, int* element) {
    if (index < 1 || index > l->length || index >= maxSize) {
        printf("the node you delete does not exist");
        return 0;
    }
    *element = l->date[index - 1];
    for (int j = index - 1; j < l->length; j++) {
        l->date[j] = l->date[j + 1];
    }
    l->length--;
    return 1;
}

/**
 * @brief 打印链表
 *
 * @param l
 */
void ListPrint(SqList l) {
    if (l.length == 0) {
        printf("there is no data\n");
        return;
    }
    for (int i = 0; i < l.length; i++) {
        printf("%d ", l.date[i]);
    }
    printf("\n");
}

/**
 * @brief 销毁链表
 *
 * @param l
 */
void DestroyList(SqList* l) {
    free(l->date);
    free(l);
}

/**
 * @brief 定位链表
 *
 * @param l
 * @param element 要定位的元素
 * @return int -1表示未找到
 */
int LocateElem(SqList l, int element) {
    for (int i = 0; i < l.length; i++) {
        if (l.date[i] == element)
            return i + 1;
    }
    return -1;
}

int GetElem(SqList l, int index) {
    if (index < l.length || index > l.length) {
        printf("the node you want to get does not exist\n");
        return -1;
    }
    return l.date[index - 1];
}

int main() {
    // SqList* list = (SqList*)malloc(sizeof(SqList));
    SqList list;
    InitList(&list);
    ListInsert(&list, 1, 2);
    ListInsert(&list, 1, 1);
    ListInsert(&list, 3, 3);
    int number;
    ListDelete(&list, 3, &number);
    printf("the number you delete is %d\n", number);
    printf("the number you locate is %d\n", LocateElem(list, 2));
    ListPrint(list);
}