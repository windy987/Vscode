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
    int r; // 矩阵行数
    int c; // 矩阵列数
    int n; // 非零元个数
} TriMatrix;

void convert(TriMatrix T, TriMatrix &M)
{
    M.r = T.c;
    M.c = T.r;
    M.n = T.n;
    int k = 1;
    for (int i = 1; i <= T.c; i++) // 按列遍历原矩阵
    {
        for (int j = 1; j <= T.n; j++) // 从第一个三元组开始遍历所有三元组
        {
            if (T.data[j].col == i)
            {
                // 进行转置并存储
                M.data[k].row = T.data[j].col;
                M.data[k].col = T.data[j].row;
                M.data[k].e = T.data[j].e;
                k++;
            }
        }
    }
}

// 按稠密矩阵形式输出
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
