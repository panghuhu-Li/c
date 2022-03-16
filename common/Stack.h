#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *stk;
    int stackSize;
    int stackCapacity;
} Stack;

Stack *stackCreate(int cpacity)
{
    Stack *returnStack = (Stack *)malloc(sizeof(Stack));
    returnStack->stackCapacity = cpacity;
    returnStack->stk = (int *)malloc(sizeof(int) * cpacity);
    returnStack->stackSize = 0;
    return returnStack;
}

void stackPush(Stack *obj, int x)
{
    obj->stk[obj->stackSize]=x;
    obj->stackSize++;
}

int stackPop(Stack *obj)
{
    return obj->stk[--(obj->stackSize)];
}

int stackTop(Stack *obj)
{
    return obj->stk[obj->stackSize-1];
}

bool stackEmpty(Stack *obj)
{
    return obj->stackSize==0;
}

void stackFree(Stack *obj)
{
    free(obj->stk);
}