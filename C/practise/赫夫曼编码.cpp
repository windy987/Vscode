#include <iostream>
using namespace std;

typedef struct Hufnode
{
    int weight;
    int parent;
    int lchild;
    int rchild;
} Hufnode;

void merge(Hufnode HF[], int n)
{
    int k = n; // 用于标记新结点的下标
    for (int i = 1; i <= n - 1; i++)
    {
        int min1 = 100000, s1 = 0; // 最小的权值及其下标
        int min2 = 100000, s2 = 0; // 次小的权值及其下标
        for (int i = 1; i <= k; i++)
        {
            // 只找最顶层的结点
            if (HF[i].parent == 0)
            {
                // 找到权值最小的两个结点
                if (HF[i].weight < min1)
                {
                    min2 = min1;
                    s2 = s1;
                    min1 = HF[i].weight;
                    s1 = i;
                }
                else if (HF[i].weight < min2)
                {
                    min2 = HF[i].weight;
                    s2 = i;
                }
            }
        }
        // 合并新结点
        k++;
        HF[k] = {HF[s1].weight + HF[s2].weight, 0, s1, s2};
        HF[s1].parent = k;
        HF[s2].parent = k;
    }
}

void convert(Hufnode HF[], int n, char a[100][100])
{
    int k = 1;   // 标记译码下标
    char c[100]; // 临时存译码
    for (int i = 1; i <= n; i++)
    {
        int t = 0; // 标记译码位数并在顶层循环开始时复位
        int l = i;
        while (HF[l].parent != 0)
        {
            int p = HF[l].parent;
            if (HF[p].lchild == l) // 如果是左子树
            {
                c[t++] = '0';
            }
            else if (HF[p].rchild == l) // 如果是右子树
            {
                c[t++] = '1';
            }
            l = p;
        }
        // 将临时译码转存至二维数组
        int h = 0;
        t--;
        for (t; t >= 0; t--)
        {
            a[k][h++] = c[t];
        }
        a[k][h] = '\0';
        k++;
    }
}

int main()
{
    Hufnode HF[10];
    HF[1] = {2, 0, 0, 0}; // C
    HF[2] = {4, 0, 0, 0}; // A
    HF[3] = {2, 0, 0, 0}; // S
    HF[4] = {3, 0, 0, 0}; // T
    HF[5] = {3, 0, 0, 0}; // ;

    char a[100][100];
    merge(HF, 5);
    convert(HF, 5, a);

    char b[20] = "CAS;CAT;SAT;AT";
    for (int i = 0; i <= 20; i++)
    {
        if (b[i] == 'C')
            cout << a[1];
        else if (b[i] == 'A')
            cout << a[2];
        else if (b[i] == 'S')
            cout << a[3];
        else if (b[i] == 'T')
            cout << a[4];
        else if (b[i] == ';')
            cout << a[5];
    }
}
