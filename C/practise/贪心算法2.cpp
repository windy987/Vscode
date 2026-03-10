// U535982 C-小梦的AB交换
// 题目描述
// 小梦有一个长度为 2*n 的 AB 串 s，其中恰好有 n 个 "A" 和 n 个 "B"。
// 他可以选择两个不同位置 i、j，交换 s[i] 和 s[j]。
// 问至少需要多少次操作，才能使相邻字符不相同。
// 输入格式
// 第一行一个正整数 T，表示数据组数。
// 每组数据第一行为正整数 n，第二行为长度为 2*n 的字符串 s，只含 "A" 和 "B"。
// 输出格式
// 对于每组测试数据，输出一行一个整数，表示最少操作次数。
// 样例输入
// 2
// 3
// AAABBB
// 3
// ABAABB
// 样例输出
// 1
// 1
// 样例解释
// 第一组：交换 s[2]=A 和 s[5]=B，得到 "ABABAB"，一次交换即可。
// 数据范围
// 令 N 表示 T 组数据中 n 的总和。
// 50% 的数据：T=1，1<=N<=3。
// 全部数据：1<=T<=100，1<=N<=10^6。

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // int n;
    // cin >> n;
    // vector<char> v(2 * n);
    // for (int i = 0; i < 2 * n; i++)
    //     cin >> v[i];
    // if (v[0] == 'a')
    // {
    //     for (int i = 1; i < 2 * n; i++)
    //     {
    //         int p;
    //         if (i % 2 != 0)
    //         {
    //             if (v[i] != 'b')
    //                 p = i;
    //             else
    //                 continue;
    //         }
    //         else
    //         {
    //             if (v[i] != 'a')
    //                 swap(v[p], v[i]);
    //             else
    //                 continue;
    //         }
    //     }
    // }
    // for (int i = 0; i < 2 * n; i++)
    //     cout << v[i];
    int n;
    cin >> n;
    vector<char> v(2 * n);
    for (int i = 0; i < 2 * n; i++)
        cin >> v[i];
    int count1 = 0;
    int count2 = 0;
    if (v[0] == 'b')
        count1++;
    if (v[0] == 'a')
        count2++;
    for (int i = 1; i < 2 * n; i++)
    {
        if (i % 2 == 1)
        {
            if (v[i] != 'b')
                count1++;
        }
        else
        {
            if (v[i] != 'a')
                count1++;
        }
    }
    for (int i = 1; i < 2 * n; i++)
    {
        if (i % 2 == 1)
        {
            if (v[i] != 'a')
                count2++;
        }
        else
        {
            if (v[i] != 'b')
                count2++;
        }
    }
    cout << count1 << endl;
    cout << count2 << endl;
    cout << min(count1 / 2, count2 / 2);
}