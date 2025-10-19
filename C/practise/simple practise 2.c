/*
📌 题目 2：计算 1 到 N 的和

描述
用户输入一个正整数 N，计算并输出从 1 到 N 的整数和。

示例

输入：5
输出：1 到 5 的和是 15


考点

for 循环

累加求和

基本变量使用
*/

#include <stdio.h>
int main()
{
    int N, i, sum = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; i++)
    {
        sum += i;
        printf("%d\n", sum);
    }
    printf("the sum is %d", sum);
}
