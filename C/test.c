/*
📌 题目 1：判断奇偶数

描述
编写一个程序，从用户输入一个整数，判断它是奇数还是偶数，并输出结果。

示例输入输出

输入：7
输出：7 是奇数
*/

#include <stdio.h>
int main()
{
    int a;
    scanf("%d", &a);
    if (a % 2 == 0)
        printf("%d is even number", a);
    else
        printf("%d is odd number", a);
}
