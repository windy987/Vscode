// 问题描述
// 在 m 行 n 列的棋盘上有一个中国象棋中的马，马走日字且只能向右走。
// 请找到可行路径的条数，使得马从棋盘的左上角 (1,1) 走到右下角 (m,n)。
// Tip：马向右走指从 (X,Y) 走到 (X+2, Y+1) 或 (X+1, Y+2) 位置

// 输入描述
// 一行，两个正整数 n m（1≤n,m≤15）。

// 输出描述
// 一行，表示相应的路径条数。

// 样例输入
// 4 4

// 样例输出
// 2

#include <bits/stdc++.h>
using namespace std;

int m, n;
int counts = 0;
// int maps[17][17] = {0};

void fun(int x, int y)
{
    if (x == m && y == n)
    {
        counts++;
        return;
    }
    else
    {
        if (x + 2 <= m && y + 1 <= n)
            fun(x + 2, y + 1);
        if (x + 1 <= m && y + 2 <= n)
            fun(x + 1, y + 2);
        return;
    }
}

int main()
{
    cin >> n >> m;
    fun(1, 1);
    cout << counts;
}