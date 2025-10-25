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

void initialize_rpos(int rpos[], TriMatrix T)
{
    for (int i = 1; i <= T.r + 1; ++i)
        rpos[i] = 0;

    // 记录每一行第一次出现的位置
    for (int p = 1; p <= T.n; ++p)
    {
        int r = T.data[p].row;
        if (rpos[r] == 0)
            rpos[r] = p;
    }

    rpos[T.r + 1] = T.n + 1;

    // 空行前填充
    for (int i = T.r; i >= 1; --i)
    {
        if (rpos[i] == 0)
            rpos[i] = rpos[i + 1];
    }
}

void multiplication(TriMatrix T, TriMatrix M, TriMatrix &P)
{
    P.r = T.r;
    P.c = M.c;
    P.n = 0;

    int rposT[105], rposM[105];
    initialize_rpos(rposT, T);
    initialize_rpos(rposM, M);

    int ctemp[100];
    for (int i = 1; i <= T.r; ++i)
    {
        for (int j = 1; j <= P.c; ++j)
            ctemp[j] = 0;

        int p0 = rposT[i];
        int p1 = rposT[i + 1];

        for (int p = p0; p < p1; ++p)
        {
            int k = T.data[p].col;
            int a = T.data[p].e;

            int q0 = rposM[k];
            int q1 = rposM[k + 1];

            for (int q = q0; q < q1; ++q)
            {
                int j = M.data[q].col;
                int b = M.data[q].e;
                ctemp[j] += a * b;
            }
        }

        for (int j = 1; j <= P.c; ++j)
        {
            if (ctemp[j] != 0)
            {
                ++P.n;
                P.data[P.n].row = i;
                P.data[P.n].col = j;
                P.data[P.n].e = ctemp[j];
            }
        }
    }
}

void printMatrix(const TriMatrix &T, const string &name)
{
    cout << name << endl;
    for (int i = 1; i <= T.n; ++i)
    {
        cout << "(" << T.data[i].row << ", "
             << T.data[i].col << ", "
             << T.data[i].e << ")" << endl;
    }
    cout << endl;
}

int main()
{
    TriMatrix T, M, P;

    T.r = 2;
    T.c = 3;
    T.n = 3;
    T.data[1] = {1, 2, 5};
    T.data[2] = {2, 1, 2};
    T.data[3] = {2, 3, 7};

    M.r = 3;
    M.c = 2;
    M.n = 3;
    M.data[1] = {1, 2, 3};
    M.data[2] = {2, 1, 4};
    M.data[3] = {3, 2, 6};

    multiplication(T, M, P);

    printMatrix(T, "T (左矩阵)");
    printMatrix(M, "M (右矩阵)");
    printMatrix(P, "P = T × M (结果)");

    return 0;
}