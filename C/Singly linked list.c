/*

*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

int GetElement(struct Node *head, int i)
{
    int count = 1;
    struct Node *p = head;
    while (p != NULL)
    {
        if (count == i)
        {
            return p->data;
        }
        else
        {
            count++;
            p = p->next;
        }
    }
    return -1;
}

void Print(struct Node *head)
{
    struct Node *p = head;
    int i = 1;
    while (p != NULL)
    {
        printf("第%d个数据是%d\n", i, p->data);
        i++;
        p = p->next;
    }
}

int Insert(struct Node **head, struct Node *newnode, int i)
{
    struct Node *p = *head;
    int count = 1;

    if (i == 1)
    {
        newnode->next = *head;
        *head = newnode;
        return 1;
    }
    else
    {
        while (p != NULL)
        {
            if (count == i - 1)
            {
                newnode->next = p->next;
                p->next = newnode;
                return 1;
            }
            count++;
            p = p->next;
        }
    }
    return -1;
}

int Delete(struct Node **head, int i)
{
    struct Node *p = *head;
    int count = 1;

    if (i == 1)
    {
        *head = p->next;
        return 1;
    }
    else
    {
        while (p != NULL)
        {
            if (count == i - 1)
            {
                p->next = p->next->next;
                return 1;
            }
            count++;
            p = p->next;
        }
    }
    return -1;
}

int main()
{

    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    head->data = 10;
    head->next = NULL;

    struct Node *second = (struct Node *)malloc(sizeof(struct Node));
    second->data = 20;
    second->next = NULL;

    struct Node *third = (struct Node *)malloc(sizeof(struct Node));
    third->data = 30;
    third->next = NULL;

    head->next = second;
    second->next = third;

    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->data = 66;
    newnode->next = NULL;

    if (Delete(&head, 2))
        printf("成功删除第2个节点\n");

    Print(head);

    free(head);
    free(second);
    free(third);
}
