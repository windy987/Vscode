#include <iostream>
using namespace std;

typedef struct BiTNode
{
    int data;
    BiTNode *lchild;
    BiTNode *rchild;
} BiTNode;

typedef struct StackNode
{
    BiTNode *data;
    StackNode *next;
} StackNode;

void pop(StackNode **top)
{
    if (*top == NULL)
    {
        cout << "出栈时访问空指针" << endl;
        return;
    }
    StackNode *p = *top;
    *top = (*top)->next;
    delete p;
}

void push(StackNode **top, BiTNode *d)
{
    StackNode *p = new StackNode{d, *top};
    *top = p;
}

void visit(BiTNode *T) { cout << T->data << ' '; }

void Preorder_traversal(BiTNode *T)
{
    BiTNode *p = T;
    StackNode *top = NULL;
    while (p != NULL || top != NULL)
    {
        while (p != NULL)
        {
            visit(p);              // 先根
            if (p->rchild != NULL) // 右子树入栈
            {
                push(&top, p->rchild);
            }
            p = p->lchild; // 前进到左子树
        }
        p = top->data;
        pop(&top);
    }
}

int main()
{
    //          1
    //       /     \
    //     2         3
    //   /   \     /   \
    //  4     5   6     7
    //       / \
    //      8   9

    // 定义节点指针
    BiTNode *A, *B, *C, *D, *E, *F, *G, *H, *I;

    // 分配内存
    A = new BiTNode;
    B = new BiTNode;
    C = new BiTNode;
    D = new BiTNode;
    E = new BiTNode;
    F = new BiTNode;
    G = new BiTNode;
    H = new BiTNode;
    I = new BiTNode;

    // 赋值
    A->data = 1;
    B->data = 2;
    C->data = 3;
    D->data = 4;
    E->data = 5;
    F->data = 6;
    G->data = 7;
    H->data = 8;
    I->data = 9;

    // 建立关系
    A->lchild = B;
    A->rchild = C;
    B->lchild = D;
    B->rchild = E;
    C->lchild = F;
    C->rchild = G;
    D->lchild = NULL;
    D->rchild = NULL;
    E->lchild = H;
    E->rchild = I;
    F->lchild = NULL;
    F->rchild = NULL;
    G->lchild = NULL;
    G->rchild = NULL;
    H->lchild = NULL;
    H->rchild = NULL;
    I->lchild = NULL;
    I->rchild = NULL;

    Preorder_traversal(A);

    return 0;
}
