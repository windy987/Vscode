// 八皇后问题递归解法
// 棋盘8X8
#include <bits/stdc++.h>
using namespace std;

int table[9];
int column[9];
int diagonal[16];
int ans = 0;

void solve(int row)
{
    int col; // 打算放置皇后的纵坐标
    if (row == 9)
        ans++;
    else
    {
        for (col = 1; col <= 8; col++)
        {
            // 放置合法
            if (column[col] == 0 && diagonal[row - col] == 0 && diagonal[row + col] == 0)
            {
                table[row] = col; // 记录皇后位置
                column[col] = 1;  // 数据更新
                diagonal[row - col] = 1;
                diagonal[row + col] = 1;
                solve(row + 1);
                // table[row] = 0;
                column[col] = 0; // 撤掉皇后
                diagonal[row - col] = 0;
                diagonal[row + col] = 0;
            }
        }
    }
}

int main()
{
}