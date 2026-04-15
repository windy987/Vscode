// 题目描述
// 已知 n 个整数 x1, x2, ..., xn，以及 1 个整数 k（k < n）。从 n 个整数中任选 k 个整数相加，可分别得到一系列的和。
// 例如当n=4，k=3，4 个整数分别为 3, 7, 12, 19 时，可得全部的组合与它们的和为：
// 3+7+12=22 3+7+19=29 7+12+19=38 3+12+19=34
// 现在，要求你计算出和为素数共有多少种。
// 例如上例，只有一种的和为素数：3+7+19=29。

// 输入格式
// 第一行两个空格隔开的整数 n, k（1 <= n <= 20，k < n）。
// 第二行 n 个整数，分别为 x1, x2, ..., xn（1 <= xi <= 5×10^6）。

// 输出格式
// 输出一个整数，表示种类数。

// 输入输出样例
// 输入：
// 4 3
// 3 7 12 19

// 输出：
// 1

#include <bits/stdc++.h>
using namespace std;

bool is_prime(int n)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (int i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int n, k;
int numbers[20];
// int visited[20] = {0};
int ans = 0;

// 从n个中选k个
void fun(int num, int start, int sum)
{
    if (num == k)
    {
        if (is_prime(sum))
            ans++;
    }
    else
    {
        for (int i = start; i < n; i++)
            fun(num + 1, i + 1, sum + numbers[i]);
    }
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> numbers[i];
    fun(0, 0, 0);
    cout << ans;
}