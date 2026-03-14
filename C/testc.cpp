// 给定图G，构造图G的邻接矩阵；
// 分别用Dijkstra算法和Floyd算法求A到D的最短路径；
// 思考：最短路径是否唯一呢？如果不唯一，该如何修改算法，求出所有最短路径呢？
// 用Prim算法求图G的最小生成树；
// 建立自己的图论程序库。
// 将上述问题的程序及计算结果写成实验报告上传至“学习通”。
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9; // 表示没有连接边
const int n = 8;

char vex[n] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

int G[n][n] = {
    // A    B    C    D    E    F    G    H
    {0, 4, INF, INF, 7, INF, 11, INF}, // A
    {4, 0, 2, INF, 6, INF, INF, INF},  // B
    {INF, 2, 0, 9, 1, 8, INF, INF},    // C
    {INF, INF, 9, 0, INF, 1, INF, 3},  // D
    {7, 6, 1, INF, 0, 10, 9, 4},       // E
    {INF, INF, 8, 1, 10, 0, INF, 2},   // F
    {11, INF, INF, INF, 9, INF, 0, 5}, // G
    {INF, INF, INF, 3, 4, 2, 5, 0}     // H
};

// 下标映射为数字0-7
int idxOf(char ch)
{
    for (int i = 0; i < n; ++i)
    {
        if (vex[i] == ch)
            return i;
    }
    return -1;
}

void dijkstra(char sChar, char tChar)
{
    int s = idxOf(sChar);
    int t = idxOf(tChar);

    if (s == -1 || t == -1)
    {
        cout << "顶点输入错误" << endl;
        return;
    }

    vector<int> dist(n, INF), pre(n, -1), vis(n, 0);
    dist[s] = 0;

    for (int i = 0; i < n; ++i)
    {
        int u = -1, mind = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!vis[j] && dist[j] < mind)
            {
                mind = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;
        vis[u] = 1;

        for (int v = 0; v < n; ++v)
        {
            if (!vis[v] && G[u][v] != INF && dist[u] + G[u][v] < dist[v])
            {
                dist[v] = dist[u] + G[u][v];
                pre[v] = u;
            }
        }
    }

    if (dist[t] == INF)
    {
        cout << vex[s] << " 到 " << vex[t] << " 不连通" << endl;
        return;
    }

    vector<int> path;
    for (int cur = t; cur != -1; cur = pre[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());

    cout << "最短距离: " << dist[t] << endl;
    cout << "最短路径: ";
    for (size_t i = 0; i < path.size(); ++i)
    {
        cout << vex[path[i]];
        if (i + 1 < path.size())
            cout << " -> ";
    }
    cout << endl;
}

void dijkstra_fix(char sChar, char tChar)
{
    int s = idxOf(sChar);
    int t = idxOf(tChar);

    vector<int> dist(n, INF), vis(n, 0);

    // 改成“多前驱”结构，保存所有可达到最短距离的前驱
    vector<vector<int>> pre(n);

    dist[s] = 0;

    for (int i = 0; i < n; ++i)
    {
        int u = -1, mind = INF;
        for (int j = 0; j < n; ++j)
        {
            if (!vis[j] && dist[j] < mind)
            {
                mind = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;
        vis[u] = 1;

        for (int v = 0; v < n; ++v)
        {
            if (!vis[v] && G[u][v] != INF)
            {
                int nd = dist[u] + G[u][v];

                // 覆盖 dist[v]，并清空旧前驱，只保留 u
                if (nd < dist[v])
                {
                    dist[v] = nd;
                    pre[v].clear();
                    pre[v].push_back(u);
                }
                // 新增一个前驱 u，表示又找到一条最短路
                else if (nd == dist[v])
                {
                    pre[v].push_back(u);
                }
            }
        }
    }

    cout << "最短距离: " << dist[t] << '\n';
    cout << "所有最短路径:\n";

    // 用 DFS 按 pre 回溯，枚举并打印所有最短路径
    vector<int> path;
    path.push_back(t);

    auto dfs = [&](auto&& self, int cur) -> void
    {
        if (cur == s)
        {
            for (int i = (int)path.size() - 1; i >= 0; --i)
            {
                cout << vex[path[i]];
                if (i > 0)
                    cout << " -> ";
            }
            cout << '\n';
            return;
        }

        for (int p : pre[cur])
        {
            path.push_back(p);
            self(self, p);
            path.pop_back();
        }
    };

    dfs(dfs, t);
}

void floyd(char sChar, char tChar)
{
    int s = idxOf(sChar);
    int t = idxOf(tChar);

    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> nxt(n, vector<int>(n, -1)); // 记录路径上的下一跳

    // 初始化
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            dist[i][j] = G[i][j];
            if (i == j)
                dist[i][j] = 0;
            if (G[i][j] != INF && i != j)
                nxt[i][j] = j;
        }
    }

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            if (dist[i][k] == INF)
                continue;
            for (int j = 0; j < n; ++j)
            {
                if (dist[k][j] == INF)
                    continue;

                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nxt[i][j] = nxt[i][k]; // 更新路径：先走 i->k 的第一跳
                }
            }
        }
    }

    cout << "最短距离: " << dist[s][t] << '\n';
    cout << "最短路径: ";

    int cur = s;
    cout << vex[cur];
    while (cur != t)
    {
        cur = nxt[cur][t];
        cout << " -> " << vex[cur];
    }
    cout << '\n';
}

void floyd_fix(char sChar, char tChar)
{
    int s = idxOf(sChar); // 默认输入正确，不做检测
    int t = idxOf(tChar);

    vector<vector<int>> dist(n, vector<int>(n, INF));

    // 修改1：原来 nxt[i][j] 只存一个“下一跳”
    // 现在改成 nexts[i][j] 存多个“下一跳”，用于恢复多条最短路
    vector<vector<vector<int>>> nexts(n, vector<vector<int>>(n));

    // 初始化
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            dist[i][j] = G[i][j];
            if (i == j)
                dist[i][j] = 0;

            if (G[i][j] != INF && i != j)
            {
                nexts[i][j].push_back(j);
            }
        }
    }

    // Floyd 三重循环
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            if (dist[i][k] == INF)
                continue;
            for (int j = 0; j < n; ++j)
            {
                if (dist[k][j] == INF)
                    continue;

                int nd = dist[i][k] + dist[k][j];

                // 修改2：更短时覆盖；相等时合并“下一跳”
                if (nd < dist[i][j])
                {
                    dist[i][j] = nd;
                    nexts[i][j] = nexts[i][k]; // 覆盖为经过 k 的第一跳集合
                }
                else if (nd == dist[i][j] && nd != INF)
                {
                    // 把 nexts[i][k] 合并到 nexts[i][j]
                    for (int x : nexts[i][k])
                        nexts[i][j].push_back(x);

                    // 去重，避免重复打印同一路径
                    sort(nexts[i][j].begin(), nexts[i][j].end());
                    nexts[i][j].erase(unique(nexts[i][j].begin(), nexts[i][j].end()), nexts[i][j].end());
                }
            }
        }
    }

    cout << "最短距离: " << dist[s][t] << '\n';
    cout << "所有最短路径:\n";

    // 修改3：DFS 按“多下一跳”枚举并打印所有最短路径
    vector<int> path;
    vector<int> vis(n, 0); // 防止路径回环（稳妥处理）

    path.push_back(s);
    vis[s] = 1;

    auto dfs = [&](auto&& self, int u) -> void
    {
        if (u == t)
        {
            for (int i = 0; i < (int)path.size(); ++i)
            {
                cout << vex[path[i]];
                if (i + 1 < (int)path.size())
                    cout << " -> ";
            }
            cout << '\n';
            return;
        }

        for (int v : nexts[u][t])
        {
            if (vis[v])
                continue;
            vis[v] = 1;
            path.push_back(v);
            self(self, v);
            path.pop_back();
            vis[v] = 0;
        }
    };

    dfs(dfs, s);
}

int main()
{
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         if (G[i][j] == INF)
    //             cout << "INF ";
    //         else
    //             cout << G[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // return 0;
    // dijkstra('A', 'D');
    // cout << '\n';
    // dijkstra_fix('A', 'D');
    // cout << '\n';
    floyd('A', 'D');
    return 0;
}
