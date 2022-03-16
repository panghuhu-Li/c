#include "ArrayList.h"
#include <stdio.h>
#include <stdlib.h>

int *decode(int *encoded, int encodedSize, int first, int *returnSize);

int main()
{
    ArrayList *head = New_ArrayList();
    ArrayList_Add(head, 2);
    ArrayList_Add(head, 3);
    printList(head);
    printf("长度为：%d", lenArrayList(head));

    // int encode[3] = {1, 2, 3};
    // int *returnSize = (int *)malloc(4 * sizeof(int));
    // int *result = decode(encode, 3, 1, returnSize);
    // for (int i = 0; i < 4; i++)
    // {
    //     printf("%d  ", result[i]);
    // }
}

int *decode(int *encoded, int encodedSize, int first, int *returnSize)
{
    int *arr = (int *)malloc((encodedSize + 1) * sizeof(int));
    arr[0] = first;
    for (int i = 0; i < encodedSize; i++)
    {
        arr[i + 1] = encoded[i] ^ arr[i];
    }
    *returnSize = encodedSize + 1;
    return arr;
}