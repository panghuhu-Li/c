#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int number;
    char name[20];
    struct Student *next;
};

typedef struct
{
    int *elem;
    int length;
    int listsize;
} SqList;

//顺序表插入
int *insert(int a[], int number, int insertNumber, int size);
//链表连接
void structLink(struct Student *a, struct Student *b);

//创建线性表
void Creat(SqList *l, int length, int listsize);
//打印线性表
void DispList(SqList *l);
//线性表反转
void ListOppose(SqList *l);
//单链表的反转
struct Student *reverse(struct Student *head);

int main()
{
    printf("数据结构2.11题：：\n");
    int a[] = {1, 2, 2, 3, 3, 4, 5, 7, 9};
    int number = sizeof(a) / sizeof(a[0]);
    int insertNumber = 7;
    for (int i = 0; i < number; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    int *b;
    b = insert(a, number, 7, sizeof(a[0]));
    for (int i = 0; i < number + 1; i++)
    {
        printf("%d ", b[i]);
    }

    printf("\n");
    printf("----------------\n");
    printf("数据结构2.15题：：\n");

    struct Student head1 = {0, "0", NULL};
    struct Student a1 = {5468, "Li"};
    struct Student b1 = {5556, "Liu"};
    struct Student c1 = {5319, "Zhang"};

    struct Student head2 = {0, "0", NULL};
    struct Student a2 = {5468, "Li"};
    struct Student b2 = {5556, "Liu"};
    struct Student c2 = {5319, "Zhang"};
    struct Student d2 = {5986, "Wang"};

    struct Student *ha = &head1;
    head1.next = &a1;
    a1.next = &b1;
    b1.next = &c1;
    c1.next = NULL;
    struct Student *hc = ha;

    struct Student *hb = &head2;
    head2.next = &a2;
    a2.next = &b2;
    b2.next = &c2;
    c2.next = &d2;
    d2.next = NULL;

    int n = 3, m = 4;

    if (n >= m)
    {
        structLink(hb, ha);
        while (hb != NULL)
        {
            hb = hb->next;
            printf("学号%d 姓名%s\n", hb->number, hb->name);
        }
    }
    else
    {
        structLink(ha, hb);
        while (ha != NULL)
        {
            if (ha->next == NULL)
                break;
            ha = ha->next;

            printf("学号%d 姓名%s\n", ha->number, ha->name);
        }
    }

    printf("----------------\n");
    printf("数据结构2.21题：：\n");

    SqList m1;
    SqList *l = &m1;
    int length = 5;
    int listsize = 10;
    Creat(l, length, listsize);
    DispList(l);
    ListOppose(l);
    DispList(l);

    printf("----------------\n");
    printf("数据结构2.22题：：\n");

    hc = reverse(hc);
    while (hc != NULL)
    {
        if (hc->next == NULL)
            break;
        printf("学号%d 姓名%s\n", hc->number, hc->name);
        hc = hc->next;
    }
}

//插入线性表
int *insert(int a[], int number, int insertNumber, int size)
{
    int *b = (int *)malloc((number + 1) * size);
    int *start = b;
    int count;
    for (int i = 0; i < number + 1; i++)
    {
        if (i == number)
        {
            b[number] = insertNumber;
        }
        if (insertNumber >= a[i] && insertNumber < a[i + 1])
        {
            b[i] = a[count];
            //将元素插入
            b[++i] = insertNumber;
        }
        b[i] = a[count];
        count++;
    }
    return start;
}

//链表连接
void structLink(struct Student *a, struct Student *b)
{
    //记录头结点
    struct Student *c = a;
    //找到尾结点
    while (a->next != NULL)
    {
        a = a->next;
    }
    a->next = b->next;
    //将头地址给a
    a = c;
}

//创建线性表
void Creat(SqList *l, int length, int listsize)
{
    (*l).elem = (int *)malloc(listsize * sizeof(int));
    if (!(*l).elem)
        exit(1);
    for (int *p = (*l).elem; p < (*l).elem + length; p++)
    {
        scanf("%d", p);
    }
    (*l).length = length;
    (*l).listsize = listsize;
}

//打印线性表
void DispList(SqList *l)
{
    for (int i = 0; i < (*l).length; i++)
        printf("%d ", (*l).elem[i]);
    printf("\n");
    printf("该表长度为:%d\n", (*l).length);
}

//线性表反转
void ListOppose(SqList *l)
{
    int i;
    int x;
    for (i = 0; i < (*l).length / 2; i++)
    {
        x = (*l).elem[i];
        (*l).elem[i] = (*l).elem[(*l).length - i - 1];
        (*l).elem[(*l).length - i - 1] = x;
    }
}

//单链表反转
struct Student *reverse(struct Student *head)
{
    struct Student *a = head;
    struct Student *p, *q;
    p = q = head->next;
    while (p != NULL)
    {
        p = p->next;
        q->next = a;
        a = q;
        q = p;
    }
    head->next = NULL;
    return a;
}