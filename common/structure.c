#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    for (int i = 0; i < numsSize; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if (nums[i] + nums[j] == target)
            {
                int *aim = malloc(sizeof(int) * 2);
                aim[0] = i;
                aim[1] = j;
                *returnSize = 2;
                return aim;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

int measureDepth(struct TreeNode *node, int depth)
{
    if (node == NULL)
        return depth;
    int letfDepth = measureDepth(node->left, depth + 1);
    int rightDepth = measureDepth(node->right, depth + 1);
    if (letfDepth <= rightDepth)
        return rightDepth;
    return letfDepth;
}

int maxDepth(struct TreeNode *root)
{
    return measureDepth(root, 1);
}

int isValidSerialization(char *preorder)
{
    int n = strlen(preorder);
    int stk[n], top = 0;
    int i = 0;
    stk[top++] = 1;
    while (i < n)
    {
        if (!top)
        {
            return 0;
        }
        if (preorder[i] == ',')
        {
            i++;
        }
        else if (preorder[i] == '#')
        {
            stk[top - 1] -= 1;
            if (stk[top - 1] == 0)
            {
                top--;
            }
            i++;
        }
        else
        {
            // 读一个数字
            while (i < n && preorder[i] != ',')
            {
                i++;
            }
            stk[top - 1] -= 1;
            if (stk[top - 1] == 0)
            {
                top--;
            }
            stk[top++] = 2;
        }
    }

    return !top ? 1 : 0;
}

int main()
{
    printf("%d", isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#"));
}