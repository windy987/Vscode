#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

typedef struct stack
{
    char data;
    stack *next;
} stack;

void push(stack **top, char c)
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->data = c;
    s->next = *top;
    *top = s;
}

// tmp保存弹出的结点数据
void pop(stack **top, char &tmp)
{
    stack *t = *top;
    *top = (*top)->next;
    tmp = t->data;
    free(t);
}

// 记录优先级
int pri(char op)
{
    switch (op)
    {
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    case '(':
    case '[':
    case '{':
    case '#': //'#'视为最低优先级
        return 0;
    default:
        return 0;
    }
}

// 判断优先级,如果b比a优先级低则返回1,否则返回0
int compare(char a, char b)
{
    if (b == '(' || b == '[' || b == '{' || b == '#')
        return 1; // 遇到左括号/哨兵就停弹
    return pri(b) < pri(a);
}

void convert(char exp[], char c[], stack **top)
{
    int k = 0;
    int i = 1;
    char tmp;
    push(top, '#');
    while (exp[i] != '#')
    {
        // 如果是数字或者字母就放入结果数组
        if ((exp[i] >= '0' && exp[i] <= '9') || (exp[i] >= 'a' && exp[i] <= 'z') || (exp[i] >= 'A' && exp[i] <= 'Z'))
        {
            c[k++] = exp[i];
            i++;
        }
        // 若是运算符
        else
        {
            // 如果是左括号就压入栈
            if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
            {
                push(top, exp[i]);
                i++;
            }
            // 如果是运算符
            else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
            {
                // 如果当前运算符优先级更高则入栈
                if (compare(exp[i], (*top)->data))
                {
                    push(top, exp[i]);
                    i++;
                }
                // 如果当前运算符优先级小于等于栈顶,则栈顶出栈并重新比较
                else
                {
                    while (!(compare(exp[i], (*top)->data)))
                    {
                        pop(top, tmp);
                        c[k++] = tmp;
                    }
                    push(top, exp[i]);
                    i++;
                }
            }
            // 如果是右括号就出栈直到遇到左括号
            else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}')
            {
                while ((*top)->data != '(' && (*top)->data != '[' && (*top)->data != '{')
                {
                    pop(top, tmp);
                    c[k++] = tmp;
                }
                // 最后让左括号出栈
                pop(top, tmp);
                i++;
            }
        }
    }
    // 扫描完成后让栈中运算符全部弹出
    while ((*top)->data != '#')
    {
        pop(top, tmp);
        c[k++] = tmp;
    }
    c[k] = '\0';
}

int main()
{
    char exp[100];
    char c[100];
    stack *top = NULL;
    cout << "请输入表达式";
    cin >> exp;
    convert(exp, c, &top);

    int i = 0;
    while (c[i])
    {
        cout << c[i];
        i++;
    }
}