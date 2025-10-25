#include <iostream>
using namespace std;

typedef struct
{
    int row; // 行下标
    int col; // 列下标
    int e;   // 数值
} triple;

typedef struct
{
    triple data[100];
    int r; // 行数
    int c; // 列数
    int n; // 非零元个数
} TriMatrix;

void convert(TriMatrix T, TriMatrix &M)
{
    // 预处理num数组，存储每列的非零元个数
    int num[T.c] = {0};
    for (int i = 1; i <= T.n; i++) // 按行遍历三元组
    {
        num[T.data[i].col]++;
    }

    // 预处理cpot数组，存储每列第一个非零元应该在转置矩阵中的位置
    int cpot[T.c];
    cpot[1] = 1;
    for (int i = 2; i <= T.c; i++)
    {
        cpot[i] = cpot[i - 1] + num[i - 1];
    }

    M.c = T.r;
    M.r = T.c;
    M.n = T.n;
    for (int i = 1; i <= T.n; i++) // 按行遍历三元组并挨个转置存储到转置矩阵中
    {
        int co = T.data[i].col;
        int q = cpot[co];
        M.data[q].col = T.data[i].row;
        M.data[q].row = T.data[i].col;
        M.data[q].e = T.data[i].e;
        cpot[co]++;
    }
}

void printMatrix(TriMatrix &T)
{
    for (int i = 1; i <= T.r; ++i)
    {
        for (int j = 1; j <= T.c; ++j)
        {
            int val = 0;
            for (int k = 1; k <= T.n; ++k)
            {
                if (T.data[k].row == i && T.data[k].col == j)
                {
                    val = T.data[k].e;
                    break;
                }
            }
            cout << val;
            if (j == T.c)
                cout << endl;
            else
                cout << ' ';
        }
    }
}

int main()
{
    TriMatrix T;
    TriMatrix M;
    T.r = 4;
    T.c = 5;
    T.n = 5;

    T.data[1] = {1, 2, 3};
    T.data[2] = {1, 4, 5};
    T.data[3] = {3, 3, 7};
    T.data[4] = {4, 1, 9};
    T.data[5] = {4, 5, 4};

    convert(T, M);
    cout << "原矩阵" << endl;
    printMatrix(T);
    cout << "转置矩阵" << endl;
    printMatrix(M);

    return 0;
}