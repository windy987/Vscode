#include <iostream>
using namespace std;

// 二叉树结点
typedef struct BiTnode
{
    int data;
    BiTnode *lchild;
    BiTnode *rchild;
} BiTnode;

// 栈
typedef struct Stacknode
{
    BiTnode *data;
    Stacknode *next;
} Stacknode;

// 弹栈
void pop(Stacknode **top)
{
    Stacknode *p = *top;
    *top = (*top)->next;
    delete p;
}

// 压栈
void push(Stacknode **top, BiTnode *d)
{
    Stacknode *p = new Stacknode{d, *top};
    *top = p;
}

// 访问当前结点
void visit(BiTnode *T) { cout << T->data << ' '; }

// 中序遍历
void traversal(BiTnode *T)
{
    // 初始化P指针遍历二叉树
    BiTnode *p = T;
    Stacknode *top = NULL;
    while (p != NULL || top != NULL)
    {
        while (p != NULL)
        {
            push(&top, p); // 根节点压栈
            p = p->lchild;
        }
        // 开始挨个弹栈
        p = top->data;
        // 访问根节点
        visit(p);
        pop(&top);
        p = p->rchild;
    }
}

int main()
{
    // 测试用二叉树
    BiTnode *A, *B, *C, *D, *E, *F, *G, *H, *I;
    A = new BiTnode;
    B = new BiTnode;
    C = new BiTnode;
    D = new BiTnode;
    E = new BiTnode;
    F = new BiTnode;
    G = new BiTnode;
    H = new BiTnode;
    I = new BiTnode;

    A->data = 1;
    A->lchild = B;
    A->rchild = C;
    B->data = 2;
    B->lchild = D;
    B->rchild = E;
    C->data = 3;
    C->lchild = F;
    C->rchild = G;
    D->data = 4;
    D->rchild = NULL;
    D->lchild = NULL;
    E->data = 5;
    E->lchild = H;
    E->rchild = I;
    F->data = 6;
    F->rchild = NULL;
    F->lchild = NULL;
    G->data = 7;
    G->rchild = NULL;
    G->lchild = NULL;
    H->data = 8;
    H->rchild = NULL;
    H->lchild = NULL;
    I->data = 9;
    I->rchild = NULL;
    I->lchild = NULL;

    traversal(A);
}
