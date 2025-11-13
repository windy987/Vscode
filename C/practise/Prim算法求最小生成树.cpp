#include <iostream>
#define Maxvexnum 10
#define Maxnum 1000000
using namespace std;

typedef struct Graph
{
    char vex[Maxvexnum];
    int arcs[Maxvexnum][Maxvexnum];
    int vexnum;
} Graph;

typedef struct closedge
{
    char vex;
    int lowcost;
} closedge;

// 找到最低权值边的下标
int Min(closedge closedge[], int vexnum, int visited[])
{
    int min = Maxnum;
    int j;
    for (int i = 0; i < vexnum; i++)
    {
        if (visited[i])
        {
            if (closedge[i].lowcost < min)
            {
                min = closedge[i].lowcost;
                j = i;
            }
        }
    }
    return j;
}

void Prim(Graph G, char u)
{
    int vexnum = G.vexnum;
    int visited[vexnum];
    int j; // 循环计数，当所有点都进入点集后停止循环
    closedge closedge[vexnum];

    // 找到初始点u所对应点下标
    int initial;
    for (int i = 0; i < vexnum; i++)
    {
        if (G.vex[i] == u)
        {
            initial = i;
            break;
        }
    }

    // 初始化
    for (int i = 0; i < vexnum; i++)
    {
        visited[i] = 1;                           // 初始化visited数组，1表示还不在已选点集中
        closedge[i].vex = G.vex[initial];         // 初始化closedge的点集
        closedge[i].lowcost = G.arcs[i][initial]; // 初始化权值
    }
    visited[initial] = 0;
    j = 1;

    while (j != vexnum)
    {
        int k = Min(closedge, vexnum, visited);              // 拿到最低权值边的下标
        visited[k] = 0;                                      // 进入已选点集
        cout << "边" << closedge[k].vex << G.vex[k] << endl; // 输出边信息
        j++;

        for (int i = 0; i < vexnum; i++) // 比较并修正最低权值
        {
            if (visited[i]) // 确保选未进入点集的点
            {
                if (G.arcs[i][k] < closedge[i].lowcost)
                {
                    closedge[i].lowcost = G.arcs[i][k];
                    closedge[i].vex = G.vex[k];
                }
            }
        }
    }
}

int main()
{
}