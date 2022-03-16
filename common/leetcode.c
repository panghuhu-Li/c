#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"
#include "Stack.h"

struct ListNode
{
    int val;
    struct ListNode *next;
};
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
struct Node
{
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

typedef struct
{
    Stack *first;
    Stack *second;
} MyQueue;

int uniquePathsWithObstacles(int **obstacleGrid, int obstacleGridSize, int *obstacleGridColSize)
{
    int cols = obstacleGridSize, rows = obstacleGridColSize[0];
    if (cols == 1)
    {
        for (int i = 0; i < rows; i++)
        {
            if (obstacleGrid[0][i] == 1)
            {
                return 0;
            }
        }
    }
    int arr[2][rows];
    int flag = 1;
    for (int i = 0; i < 2; i++)
    {
        if (obstacleGrid[i][0] == 1)
        {
            flag = 0;
        }

        arr[i][0] = flag;
    }
    flag = 1;
    for (int i = 0; i < rows; i++)
    {
        if (obstacleGrid[0][i] == 1)
        {
            flag = 0;
        }
        arr[0][i] = flag;
    }
    for (int i = 1; i < cols; i++)
    {
        for (int j = 1; j < rows; j++)
        {
            if (obstacleGrid[i][j] == 0)
            {
                arr[i % 2][j] = arr[(i - 1) % 2][j] + arr[i % 2][j - 1];
            }
            else
            {
                arr[i % 2][j] = 0;
            }
        }
    }
    return arr[(cols - 1) % 2][rows - 1];
}

int main()
{
    int i,m,n,sum;
    printf("请输入两个整数，用空格隔开：\n");
    scanf("%d%d",&m,&n);
    sum=0;
    i=m;
    while(i<=n)
    {
        sum=sum+i;
        i++;
    }
    printf("和为:%d\n",sum);
}