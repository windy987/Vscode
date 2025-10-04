#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct term
{
    float coef; // 系数
    int expn;   // 指数
    struct term *next;
} term;

void create_newterm(term **head, float coef, int expn)
{
    // 初始化新节点
    term *newterm = (term *)malloc(sizeof(term));
    newterm->coef = coef;
    newterm->expn = expn;
    newterm->next = NULL;

    // 找到尾节点
    term *p = *head;
    while (p->next != NULL)
        p = p->next;

    // 接上新节点
    p->next = newterm;
}

// 打印函数用于检查
void print_allterms(term *head)
{
    term *p = head->next;
    int first = 1;
    while (p != NULL)
    {
        float coef = p->coef;
        int expn = p->expn;

        if (!first && coef > 0)
            cout << "+";

        if (expn == 1)
        {
            if (coef == 1)
                cout << "x";
            else if (coef == -1)
                cout << "-x";
            else
                cout << coef << "x";
        }
        else
        {
            if (coef == 1)
                cout << "x^" << expn;
            else if (coef == -1)
                cout << "-x^" << expn;
            else
                cout << coef << "x^" << expn;
        }

        first = 0;
        p = p->next;
    }
    if (first)
        cout << "0";
    cout << endl;
}

void free_terms(term *head)
{
    term *p = head;
    while (p != NULL)
    {
        term *next = p->next;
        free(p);
        p = next;
    }
}

int main()
{
    // 初始化头节点(只用于标记头位置)
    term *head1 = (term *)malloc(sizeof(term));
    head1->next = NULL;
    term *head2 = (term *)malloc(sizeof(term));
    head2->next = NULL;
    term *head3 = (term *)malloc(sizeof(term));
    head3->next = NULL;

    // float coef;
    // int expn;
    // int n;
    // for (int m = 1; m <= 2; m++)
    // {
    //     cout << "请输入第" << m << "个多项式的项数" << endl;
    //     cin >> n;
    //     for (int i = 1; i <= n; i++)
    //     {
    //         cout << "请输入第" << i << "项的系数" << endl;
    //         cin >> coef;
    //         cout << "请输入第" << i << "项的指数" << endl;
    //         cin >> expn;
    //         if (m == 1)
    //             creat_newterm(&head1, coef, expn);
    //         else
    //             creat_newterm(&head2, coef, expn);
    //     }
    // }
    // print_allterms(head1);
    // print_allterms(head2);

    // x^2 - 5x^3 + 6x^4
    // x^3 + 5x^4 - 3x^7 + x^8
    create_newterm(&head1, 1.0f, 2);
    create_newterm(&head1, -5.0f, 3);
    create_newterm(&head1, 6.0f, 4);

    create_newterm(&head2, 1.0f, 3);
    create_newterm(&head2, 5.0f, 4);
    create_newterm(&head2, -3.0f, 7);
    create_newterm(&head2, 1.0f, 8);

    print_allterms(head1);
    print_allterms(head2);

    term *a = head1->next;
    term *b = head2->next;

    while (a != NULL && b != NULL)
    {
        if (a->expn < b->expn)
        {
            create_newterm(&head3, a->coef, a->expn);
            a = a->next;
        }
        else if (a->expn == b->expn)
        {
            if (a->coef + b->coef == 0)
            {
                a = a->next;
                b = b->next;
            }
            else
            {
                create_newterm(&head3, a->coef + b->coef, a->expn);
                a = a->next;
                b = b->next;
            }
        }
        else
        {
            create_newterm(&head3, b->coef, b->expn);
            b = b->next;
        }
    }
    if (a == NULL)
    {
        while (b != NULL)
        {
            create_newterm(&head3, b->coef, b->expn);
            b = b->next;
        }
    }
    else
    {
        while (a != NULL)
        {
            create_newterm(&head3, a->coef, a->expn);
            a = a->next;
        }
    }

    print_allterms(head3);

    free_terms(head1);
    free_terms(head2);
    free_terms(head3);
}
