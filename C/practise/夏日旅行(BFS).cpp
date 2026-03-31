// 【题目描述】
// 夏天的时候，ThinkSpirit 实验室去海边玩了。蒙起眼睛的 Crush 举起了木棒，他要在大家的帮助下打西瓜。
// 沙滩可以被描述成一个 N × M 的网格，其中某些格子为不可移动的障碍物。Crush
// 始终在网格内移动，且不会走出边界。西瓜也处于一个格子上，当 Crush 走到西瓜所在格子，他就会举起木棒重重挥下。
// 好心的成员会给出提示，每个提示都会让 Crush 走向相邻（上下左右四个方向）的一个可走格子。问最少需要多少条提示，才能让
// Crush 打到西瓜？

// 【输入描述】
// 1. 第一行：两个正整数 N, M (N, M <= 50)，表示沙滩的大小。
// 2. 接下来 N 行：每行 M 个用空格隔开的 0 或 1。0 表示此格无障碍，1 表示此格为障碍物。
// 3. 最后一行：4 个整数，分别表示 Crush 的起始行号、列号以及西瓜的目标行号、列号。（行号和列号从 1 开始递增）
// 数据确保起始点与目标点都在无障碍的格点上。

// 【输出描述】
// 一个整数，表示需要的最小提示数。如果 Crush 无论如何都不能抵达西瓜所在格子，输出 -1。

// 【样例输入】
// 9 10
// 0 0 0 0 0 0 1 0 0 0
// 0 0 0 0 0 0 0 0 1 0
// 0 0 0 1 0 0 0 0 0 0
// 0 0 1 0 0 0 0 0 0 0
// 0 0 0 0 0 0 1 0 0 0
// 0 0 0 0 0 1 0 0 0 0
// 0 0 0 1 1 0 0 0 0 0
// 0 0 0 0 0 0 0 0 0 0
// 1 0 0 0 0 0 0 0 1 0
// 3 3 4 4

// 【样例输出】
// 6

#include <bits/stdc++.h>
using namespace std;

struct state
{
    int x;
    int y;
    int steps;
};

int x_move[4] = {0, 1, -1, 0};
int y_move[4] = {1, 0, 0, -1};

int maps[52][52] = {0};
int visited[52][52] = {0};

int main()
{
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
            cin >> maps[i][j];
    }
    // 给地图加一圈边用1表示
    for (int j = 0; j <= M + 1; j++)
    {
        maps[0][j] = 1;
        maps[N + 1][j] = 1;
    }
    for (int i = 0; i <= N + 1; i++)
    {
        maps[i][0] = 1;
        maps[i][M + 1] = 1;
    }
    int x, y, x_target, y_target;
    cin >> x >> y >> x_target >> y_target;
    queue<state> q;
    int steps = 0;
    q.push({x, y, steps});
    // 循环直到碰到终点
    while (!q.empty() && (q.front().x != x_target || q.front().y != y_target))
    {
        state front = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int x_currnt = front.x + x_move[i];
            int y_currnt = front.y + y_move[i];
            if (maps[x_currnt][y_currnt] != 1 && visited[x_currnt][y_currnt] != 1)
            {
                q.push({x_currnt, y_currnt, front.steps + 1});
                visited[x_currnt][y_currnt] = 1;
            }
        }
    }
    if (q.empty())
        cout << -1;
    else
        cout << q.front().steps;
}
