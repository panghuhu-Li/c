#include <stdio.h>
#include <stdlib.h>

//插入
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
            b[++i] = insertNumber;
        }
        b[i] = a[count];
        count++;
    }
    return start;
}