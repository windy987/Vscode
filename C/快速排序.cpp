#include <iostream>
using namespace std;
#define MAXSIZE 1000 // 待排顺序表最大长度
typedef int KeyType; // 关键字类型
typedef struct
{
    KeyType key;
    // InfoType otherinfol;
} Redtype; // 记录类型
typedef struct
{
    Redtype r[MAXSIZE + 1]; // r[0] 闲置或用作哨兵
    int length;
} Sqlist; // 顺序表类型

void Bubble_Sort(Sqlist &L)
{
    // 从r[1]开始,r[0]做哨兵
    for (int i = 1; i < L.length - 1; i++)
    {
        for (int j = 1; j <= L.length - i - 1; j++)
        {
            if (L.r[j + 1].key < L.r[j].key)
            {
                // 交换
                L.r[0] = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = L.r[0];
            }
        }
    }
}

// 将比选定的pivotkey小的数据放在它左边，大的放到右边
// 最终返回pivotkey的新下标
// r[0]做哨兵
int Partition(Sqlist &L, int low, int high)
{
    int pivotkey = L.r[low].key;
    while (low < high)
    {
        // high向左挪，一旦遇到比pivotkey小的就和r[low]交换
        while (low < high && L.r[high].key >= pivotkey)
            high--;
        L.r[0] = L.r[low];
        L.r[low] = L.r[high];
        L.r[high] = L.r[0];
        // low向右挪，一旦遇到比pivotkey大的就和r[high]交换
        while (low < high && L.r[low].key <= pivotkey)
            low++;
        L.r[0] = L.r[low];
        L.r[low] = L.r[high];
        L.r[high] = L.r[0];
    }
    return low;
}

// 递归写法的快速排序
void Quick_Sort_Recursion(Sqlist &L, int low, int high)
{
    if (low < high)
    {
        int pivot = Partition(L, low, high);
        Quick_Sort_Recursion(L, low, pivot - 1);
        Quick_Sort_Recursion(L, pivot + 1, high);
    }
}

// 测试数据
int main()
{
    Sqlist *L = new Sqlist;
    L->length = 9;
    L->r[1].key = 2;
    L->r[2].key = 5;
    L->r[3].key = 6;
    L->r[4].key = 2;
    L->r[5].key = 3;
    L->r[6].key = 1;
    L->r[7].key = 2;
    L->r[8].key = 4;
    Quick_Sort_Recursion(*L, 1, 8);
    // Bubble_Sort(*L);
    for (int i = 1; i < L->length; i++)
        cout << L->r[i].key << ' ';
}