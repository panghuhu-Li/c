#include <stdio.h>
#include <stdlib.h>

typedef int elementType;
/**
 * @brief 创建双向链表数据结构
 *
 */
typedef struct DNode {
    elementType data;
    struct DNode *prior, *next;
} DoubleList;

/**
 * @brief 初始化双向链表
 *
 * @return DoubleList*
 */
DoubleList* InitList() {
    DoubleList* list = (DoubleList*)malloc(sizeof(DoubleList));
    if (list == NULL) {
        printf("链表初始化失败\n");
    }
    list->next = NULL;
    list->prior = NULL;
    return list;
}

/**
 * @brief 销毁双向链表
 *
 * @param list
 * @return int 销毁成功返回1
 */
int ListDestroy(DoubleList* list) {
    DoubleList* current = list->next;
    while (current) {
        DoubleList* next = current->next;
        free(current);
        current = next;
    }
    return 1;
}

/**
 * @brief 链表的头插入
 *
 * @param list
 * @param element 插入的元素
 * @return int 插入成功返回1，失败返回0
 */
int List_HeadInsert(DoubleList* list, elementType element) {
    DoubleList* node = (DoubleList*)malloc(sizeof(DoubleList));
    if (node == NULL) {
        printf("添加的新节点初始化失败\n");
        return 0;
    }
    node->data = element;
    node->next = list->next;
    node->prior = list;
    //如果链表为空
    if (list->next != NULL) {
        list->next->prior = node;
    }
    list->next = node;
    return 1;
}

/**
 * @brief 双向链表的尾插入
 *
 * @param list
 * @param element
 * @return int
 */
int List_TailInsert(DoubleList* list, elementType element) {
    DoubleList* node = (DoubleList*)malloc(sizeof(DoubleList));
    if (node == NULL) {
        printf("添加的新节点初始化失败\n");
        return 0;
    }
    node->data = element;
    DoubleList* current = list;
    while (current->next) {
        current = current->next;
    }
    node->next = current->next;
    node->prior = current;
    current->next = node;
    return 1;
}

/**
 * @brief Get the Elem object
 *
 * @param list
 * @param index 获取的节点下标
 * @return DoubleList* 返回该节点的指针
 */
DoubleList* GetElem(DoubleList* list, int index) {
    if (index == 0) {
        return list;
    }
    if (index < 0) {
        printf("链表下标不存在\n");
        return NULL;
    }
    int j = 1;
    DoubleList* current = list->next;
    while (current && j < index) {
        current = current->next;
        j++;
    }
    return current;
}

/**
 * @brief 根据节点下标删除双向链表
 *
 * @param list
 * @param index
 * @param element 删除的双向链表的元素
 * @return int 删除成功返回1，失败返回0
 */
int ListDelete(DoubleList* list, int index, elementType* element) {
    if (index <= 0) {
        printf("要删除的下标不合法\n");
        return 0;
    }
    DoubleList* previousNode = GetElem(list, index - 1);
    if (previousNode == NULL || previousNode->next == NULL) {
        printf("要删除的节点不存在\n");
        return 0;
    }
    DoubleList* current = previousNode->next;
    previousNode->next = current->next;
    *element = current->data;
    if (current->next != NULL) {
        current->next->prior = previousNode;
    }
    free(current);
    return 1;
}

/**
 * @brief 打印双向链表的值
 *
 * @param list
 */
void ListPrint(DoubleList* list) {
    DoubleList* current = list->next;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    DoubleList* list = InitList();
    List_HeadInsert(list, 1);
    List_TailInsert(list, 2);
    ListPrint(list);
    elementType element;
    ListDelete(list, 1, &element);
    printf("%d\n", element);
    ListPrint(list);
}