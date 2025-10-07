/*
📌 题目 5：编写一个计算阶乘的函数

描述
写一个函数 long long factorial(int n)，返回 n 的阶乘，并在 main() 中调用该函数。

示例

输入：5
输出：5! = 120


考点

函数定义与调用

循环计算

基本数据类型选择（防止溢出）
*/

#include <stdio.h>
int long long factorial(int n)
{
    int i;
    int num = 1;
    for (i = 1; i <= n; i++)
        num *= i;
    return num;
}
int main()
{
    int n;
    scanf("%d", &n);
    printf("%lld", factorial(n));
}
