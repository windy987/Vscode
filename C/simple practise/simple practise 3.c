/*
📌 题目 3：找出数组中的最大值

描述
用户输入 5 个整数，存入数组中，并输出数组中的最大值。

示例

输入：3 7 2 9 5
输出：最大值是 9


考点

数组定义与输入

for 循环遍历

条件比较
*/

#include <stdio.h>
int main()
{
    int i;
    int a[5];
    // input
    for (i = 0; i < 5; i++)
        scanf("%d", &a[i]);
    // get the biggest one
    int max = a[0];
    for (i = 1; i < 5; i++)
    {
        if (a[i] > max)
            max = a[i];
    }
    printf("%d", max);
}
