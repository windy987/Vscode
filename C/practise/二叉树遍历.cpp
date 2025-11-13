#include <iostream>
using namespace std;

typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode;

// 访问当前节点的data数据
void visit(BiTNode *T)
{
    cout << T->data << endl;
}

// 前序遍历
void Preorder_traversal(BiTNode *T)
{
    if (T) // 二叉树非空
    {
        visit(T);
        Preorder_traversal(T->lchild); // 前进到左子树
        Preorder_traversal(T->rchild); // 前进到右子树
    }
}

// 中序遍历
void Inorder_traversal(BiTNode *T)
{
    if (T)
    {
        Inorder_traversal(T->lchild);
        visit(T);
        Inorder_traversal(T->rchild);
    }
}

// 后序遍历
void Postorder_traversal(BiTNode *T)
{
    if (T)
    {
        Postorder_traversal(T->lchild);
        Postorder_traversal(T->rchild);
        visit(T);
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

    Postorder_traversal(A);

    return 0;
}
