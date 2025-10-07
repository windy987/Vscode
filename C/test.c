#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 创建一个新节点
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode; // 自己指向自己
    return newNode;
}

// 在链表末尾插入新节点
void insertNode(Node **head, int data)
{
    Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node *temp = *head;
        while (temp->next != *head)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

// 打印链表
void printList(Node *head)
{
    Node *temp = head;
    if (head != NULL)
    {
        do
        {
            printf("节点数据: %d\n", temp->data);
            temp = temp->next;
        } while (temp != head);
    }
}

// 解决约瑟夫问题
int josephus(int n, int m)
{
    Node *head = NULL;

    // 创建循环链表
    for (int i = 1; i <= n; i++)
    {
        insertNode(&head, i);
    }

    Node *temp = head;
    while (temp->next != temp)
    { // 直到链表只剩一个节点
        for (int i = 1; i < m; i++)
        {
            temp = temp->next; // 移动到第 m 个节点
        }
        // 删除第 m 个节点
        printf("删除节点: %d\n", temp->data);
        Node *toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
        temp = temp->next;
    }

    int last = temp->data;
    free(temp); // 删除最后剩下的节点
    return last;
}

int main()
{
    int n, m;
    printf("请输入总人数: ");
    scanf("%d", &n);
    printf("请输入每次报数的间隔: ");
    scanf("%d", &m);

    int result = josephus(n, m);
    printf("最后剩下的人是: %d\n", result);

    return 0;
}
