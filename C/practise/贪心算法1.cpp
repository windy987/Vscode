#include <algorithm>
#include <iostream>
using namespace std;

// 题目描述
// 有一个由 n 个整数构成的数组 {a1, a2, …, an} 和一个整数 x = 0。
// 小红和小紫轮流操作，每次操作方拿走数组中的一个元素，并从数组中移除。
// 记被拿走的元素为 ai，若是小红拿走的，则会让 x 加上 ai；
// 若是小紫拿走的，则会让 x 减去 ai。
// 小红希望最终 x 尽可能小，小紫希望最终 x 尽可能大。
// 小红先手操作，请问双方都采用最优策略时，最终 x 的值是多少？
// 输入描述
// 第一行输入一个正整数 n（1 ≤ n ≤ 10^5），代表数组中的元素数量。
// 第二行输入 n 个正整数 a1, a2, …, an（1 ≤ ai ≤ 10^9），代表数组中的元素。
// 输出描述
// 一个整数，代表最终 x 的值。
// 示例1
// 输入：
// 3
// 2 3 4
// 输出：
// 3
// 说明
// 在这组样例中，过程如下：
// - 小红先手操作，拿走 2，x = 2；
// - 小紫拿走 3，x = -1；
// - 小红拿走 4，x = 3。
// 因此，最终 x = 3。
// bool is_prime(int n);
// bool is_palindrome(int n);

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    int x = a[0];
    for (int i = 1; i < n; i++)
    {
        if (i % 2 != 0)
        {
            x -= a[i];
            // cout << x << endl;
        }
        else
        {
            x += a[i];
            // cout << x << endl;
        }
    }
    cout << x;
}