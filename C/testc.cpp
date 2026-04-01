// N 架飞机准备降落到某个只有一条跑道的机场。
// 其中第 i 架飞机在 Ti 时刻到达机场上空，到达时它的剩余油料还可以继续盘旋 Di 个单位时间，即它最早可以于 Ti
// 时刻开始降落，最晚可以于 Ti + Di 时刻开始降落。降落过程需要 Li 个单位时间。
// 一架飞机降落完毕时，另一架飞机可以立即在同一时刻开始降落，但是不能在前一架飞机完成降落前开始降落。
// 请你判断 N 架飞机是否可以全部安全降落。

// 输入格式
// 输入包含多组数据。
// 第一行包含一个整数 T，代表测试数据的组数。
// 对于每组数据：
// 第一行包含一个整数 N。
// 以下 N 行，每行包含三个整数 Ti，Di，Li。

// 输出格式
// 对于每组数据，输出 YES 或 NO，代表是否可以全部安全降落。

// 输入输出样例
// 输入：
// 2
// 3
// 0 100 10
// 10 10 10
// 0 2 20
// 3
// 0 10 20
// 10 10 20
// 20 10 20

// 输出：
// YES
// NO

// 说明
// 样例说明：
// 对于第一组数据，可以安排：
// 第 3 架飞机于 0 时刻开始降落，20 时刻完成降落；
// 第 2 架飞机于 20 时刻开始降落，30 时刻完成降落；
// 第 1 架飞机于 30 时刻开始降落，40 时刻完成降落。
// 对于第二组数据，无论如何安排，都会有飞机不能及时降落。

// 数据范围
// 对于 30% 的数据，N ≤ 2。
// 对于 100% 的数据：
// 1 ≤ T ≤ 10
// 1 ≤ N ≤ 10
// 0 ≤ Ti，Di，Li ≤ 100000

#include <bits/stdc++.h>
using namespace std;

struct plane
{
    int Ti;
    int Di;
    int Li;
};

plane planes[10];
bool visited[10] = {0};
int n;

void fun(int depth, int curtime)
{
    if (depth == n)
    {
        cout << "YES";
        return;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                curtime = max(planes[i].Ti, curtime) + planes[i].Li;
                if (curtime > planes[i].Ti + planes[i].Di)
                    return;
                else
                {
                    visited[i] = 1;
                    fun(depth + 1, curtime);
                }
            }
        }
    }
}

int main()
{
}