#include <iostream>
using namespace std;

Boolean visited[MAX];
Status (*VisitFunc)(int v);
void DFSTraverse(Graph G, Status (*Visit)(int v))
{
    VisitFunc = Visit; // DFS 省去设置函数指针参数
    for (v = 0; v < G.vexnum; v++)
        visited[v] = FALSE;
    for (v = 0; v < G.vexnum; v++)
        if (!visited[v])
            DFS(G, v);
}
void DFS(Graph G, int v)
{
    visited[v] = TRUE;
    VisitFunc(v);
    for (w = FirstAdjVex(G, v); w >= 0; NextAdjVex(G, v, w))
        if (!visited[w])
            DFS(G, w);
}

void BFSTraverse(Graph G, Status (*Visit)(int v))
{
    for (v = 0; v < G.vexnum; ++v)
        visited[v] = FALSE;
    InitQueue(Q);
    for (v = 0; v < G.vexnum; ++v)
        if (!visited[v])
        {
            visited[v] = TRUE;
            Visit(v);
            EnQueue(Q, v);
            while (!QueueEmpty(Q))
            {
                DeQueue(Q, u);
                for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
                    if (!visited[w])
                    {
                        visited[w] = TRUE;
                        Visit(w);
                        EnQueue(Q, w);
                    } // if
            } // while
        } // if
} // BFSTraverse