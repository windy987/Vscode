#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct Node
{
    int number;
    struct Node *next;
} node;

// 在链表最后插入新节点
node *Insert(node *head, int number)
{
    node *p = head;
    while (p->next != head)
        p = p->next;

    node *newnode = (node *)malloc(sizeof(node));
    newnode->number = number;
    p->next = newnode;
    newnode->next = head;

    return newnode;
}

// 删除节点函数
node *Delete(node *cur, node *pre)
{
    node *p = cur;
    pre->next = cur->next;
    return p;
}

int main()
{
    int n, m;

    cout << "共有几个人?" << endl;
    cin >> n;
    cout << "数到第几个使其出列?" << endl;
    cin >> m;
    cout << endl;

    // 初始化单个节点的循环链表
    node *head = (node *)malloc(sizeof(node));
    head->number = 1;
    head->next = head;

    node *cur = head;
    node *pre;

    // 构建循环链表
    for (int i = 2; i <= n; i++)
    {
        pre = Insert(head, i);
    }

    int h = 0; // 出列的人数
    while (h != n - 1)
    {
        int count = 0;
        while (count != m)
        {
            count++;
            if (count != m)
            {
                cur = cur->next;
                pre = pre->next;
            }
        }
        count = 0;
        h++;
        node *d = Delete(cur, pre);
        cur = cur->next;
        cout << d->number << "号出列" << endl;
    }
    cout << endl;
    cout << cur->number << "号仍在列" << endl;
}
