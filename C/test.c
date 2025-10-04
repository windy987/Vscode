/*

*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

// 从头节点出发打印n个节点数据
void Print(struct Node *head, int n)
{
    struct Node *p = head;
    for (int i = 1; i <= n; i++)
    {
        printf("打印第%d个节点数据为%d\n", i, p->data);
        p = p->next;
    }
}

// 创建一个新节点并让它指向自己
struct Node *create_single_node(int value)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = value;
    node->next = node;
    return node;
}

// 插入函数
struct Node *Insert(struct Node *head, int value)
{
    if (head == NULL)
        return create_single_node(value);
    else
    {
        // 新节点
        struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
        newnode->data = value;

        // 找到头节点的前一个节点
        struct Node *p = head;
        while (p->next != head)
            p = p->next;

        // 插入
        p->next = newnode;
        newnode->next = head;
        return head;
    }
}

int main()
{
    struct Node *head = NULL;
    head = Insert(head, 1);
    for (int i = 2; i <= 4; i++)
        Insert(head, i);

    Print(head, 10);
}
