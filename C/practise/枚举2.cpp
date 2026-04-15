// 题目描述
// 小红在一个游戏里杀怪。这是个回合制游戏，小红和两只怪物相遇了。
// 第一只怪物有 a 血量，第二只怪物有 b 血量。
// 小红有两个技能：
// 第一个技能叫火球术，效果是对单体怪物造成 x 伤害。
// 第二个技能叫烈焰风暴，效果是对每只怪物造成 y 伤害。
// 小红想知道，自己最少使用多少次技能，可以击杀这两只怪物？（当怪物血量小于等于0时，视为被击杀）

// 输入描述:
// 四个正整数 a, b, x, y，用空格隔开。
// 1 ≤ a, b, x, y ≤ 20

// 输出描述:
// 小红使用技能的最少次数。

// 示例1
// 输入
// 5 2 3 1

// 输出
// 3

#include <bits/stdc++.h>
using namespace std;

// mx + ny >= a;
// px + ny >= b;
int main()
{
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    int ma_max = a / x + 1;
    int n_max = (a / y > b / y) ? (a / y + 1) : (b / y + 1);
    int p_max = b / x + 1;
    int ans = 100000000;
    for (int i = 0; i < ma_max; i++)
    {
        for (int j = 0; j < n_max; j++)
        {
            for (int q = 0; q < p_max; q++)
            {
                if (i * x + j * y >= a && q * x + j * y >= b)
                {
                    if (i + j + q < ans)
                        ans = i + j + q;
                }
            }
        }
    }
    cout << ans;
}