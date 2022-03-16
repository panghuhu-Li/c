#include <malloc.h>
#include <stdio.h>

typedef int elementType;

typedef struct List {
    elementType date;
    struct List* next;
} LinkedList;

/**
 * @brief 初始化链表
 *
 * @param list
 * @return int 返回初始化的头节点
 */
LinkedList* InitList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        printf("初始化失败\n");
        return NULL;
    }
    list->next = NULL;
    return list;
}

/**
 * @brief 链表头插入
 *
 * @param list
 * @param element 插入的元素值
 * @return int 插入成功返回1，失败返回0
 */
int List_HeadInsert(LinkedList* list, elementType element) {
    LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
    if (node == NULL) {
        printf("创建节点失败\n");
        return 0;
    }
    node->date = element;
    node->next = list->next;
    list->next = node;
    return 1;
}

/**
 * @brief 链表尾节点插入
 *
 * @param list
 * @param element 插入元素值
 * @return int 插入成功返回1，失败返回0
 */
int List_TailInsert(LinkedList* list, elementType element) {
    LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
    if (node == NULL) {
        printf("创建节点失败\n");
        return 0;
    }
    node->date = element;
    LinkedList* current = list;
    while (current->next) {
        current = current->next;
    }
    node->next = current->next;
    current->next = node;
    return 1;
}

/**
 * @brief 链表打印
 *
 * @param list
 */
void ListPrint(LinkedList* list) {
    LinkedList* current = list->next;
    while (current != NULL) {
        printf("%d ", current->date);
        current = current->next;
    }
    printf("\n");
}

/**
 * @brief Get the Elem object
 *
 * @param list
 * @param index 获取的链表下标
 * @return LinkedList* 返回查找到的节点，未查找到返回NULL
 */
LinkedList* GetElem(LinkedList* list, int index) {
    if (index < 0) {
        return NULL;
    }
    if (index == 0) {
        return list;
    }
    LinkedList* current = list->next;
    int j = 1;
    while (current && j < index) {
        current = current->next;
        j++;
    }
    return current;
}

/**
 * @brief 链表长度
 *
 * @param list
 * @return int 返回链表的长度
 */
int ListLength(LinkedList* list) {
    int number = 0;
    LinkedList* current = list->next;
    while (current) {
        current = current->next;
        number++;
    }
    return number;
}

/**
 * @brief 删除对应下标的链表节点
 *
 * @param list
 * @param index 要输出的链表下标
 * @return int 删除成功返回1，删除失败返回0;
 */
int ListDelete(LinkedList* list, int index) {
    if (index > ListLength(list)) {
        printf("要删除的节点下标超出链表长度");
        return 0;
    }
    LinkedList* previous = GetElem(list, index - 1);
    if (previous == NULL) {
        printf("删除失败不存在该节点");
        return 0;
    }
    LinkedList* deleteNode = previous->next;
    previous->next = deleteNode->next;
    free(deleteNode);
    return 1;
}

int ListInsert(LinkedList* list, elementType element, int index) {
    LinkedList* current = list;
    LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
    if (node == NULL) {
        printf("生成新节点失败\n");
        return 0;
    }
    node->date = element;
    int j = 0;
    //和GetElem中while有区别，该循环跳出来current一定不为NULL
    while (current->next && j < index - 1) {
        current = current->next;
        j++;
    }
    node->next = current->next;
    current->next = node;
    return 1;
}

int ListDertory(LinkedList* list){
    int number=1;
    LinkedList* current=list->next;
    while(current){
        LinkedList* next=current->next;
        free(current);
        current=next;
    }
    list->next=NULL;
    return 0;
}

int main() {
    LinkedList* list = InitList();
    List_HeadInsert(list, 1);
    List_TailInsert(list, 2);
    List_HeadInsert(list, 3);
    List_TailInsert(list, 4);
    ListInsert(list, 5, 5);
    ListInsert(list, 6, 1);
    ListPrint(list);
    ListDertory(list);
    ListPrint(list);
    
}
