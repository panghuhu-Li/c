#include <stdio.h>
#include <stdlib.h>

typedef int Type;

typedef struct Link
{
    Type elem;         //代表数据域
    struct Link *next; //代表指针域，指向直接后继元素
} ArrayList;

ArrayList *New_ArrayList()
{
    ArrayList *headList = (ArrayList *)malloc(sizeof(ArrayList));
    if (headList == NULL)
    {
        printf("创建头结点失败");
        exit(1);
    }
    headList->elem = 0;
    headList->next = NULL;
    return headList;
}

// 按照头结点插入
ArrayList *ArrayList_Add(ArrayList *headList, Type elem)
{
    ArrayList *newNode = (ArrayList *)malloc(sizeof(ArrayList));
    if (headList == NULL)
    {
        printf("插入结点时空间分配失败");
        exit(1);
    }
    newNode->elem = elem;
    ArrayList *firstNode = headList->next;
    headList->next = newNode;
    newNode->next = firstNode;
    return headList;
}

void printList(ArrayList *headList)
{
    if (headList->next == NULL)
    {
        printf("空");
    }
    ArrayList *tempHead = headList;
    while (tempHead->next != NULL)
    {
        tempHead = tempHead->next;
        if (tempHead->next != NULL)
            printf("%d -> ", tempHead->elem);
        else
            printf("%d ", tempHead->elem);
    }
    printf("\n");
}

int lenArrayList(ArrayList *headList)
{
    if (headList->next == NULL)
    {
        return 0;
    }
    int len = 0;
    ArrayList *tempHead = headList;
    while (tempHead->next != NULL)
    {
        tempHead = tempHead->next;
        len++;
    }
    return len;
}

//如果有相同的返回第一个位置
ArrayList *find_ArrayList(ArrayList *headList, Type elem)
{
    if (headList->next == NULL)
    {
        printf("链表为空");
        return NULL;
    }

    ArrayList *tempHead = headList;
    while (tempHead->next != NULL)
    {
        tempHead = tempHead->next;
        if (tempHead->elem == elem)
        {
            return tempHead;
        }
    }

    return NULL;
}

//如果有相同的删除第一个
int delete_ArrayList(ArrayList *headList, Type elem)
{
    ArrayList *deleteNode = find_ArrayList(headList, elem);
    if (deleteNode == NULL)
    {
        printf("不存在该元素，无法删除");
        return 0;
    }
    
}
