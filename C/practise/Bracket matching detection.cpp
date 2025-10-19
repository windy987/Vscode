#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

typedef struct stacknode
{
    char data;
    stacknode *next;
} stacknode;

// 若空栈则返回1
int stackempty(stacknode *top)
{
    if (top == NULL)
        return 1;
    else
        return 0;
}

// 入栈函数
void push(stacknode **top, char a)
{
    stacknode *s = (stacknode *)malloc(sizeof(stacknode));
    s->data = a;
    s->next = *top;
    *top = s;
}

// 出栈函数
void pop(stacknode **top)
{
    stacknode *p = *top;
    *top = (*top)->next;
    free(p);
}

// 主函数
int matching(char exp[], stacknode **top)
{
    int i;
    for (i = 0; i < strlen(exp); i++)
    {
        // 如果遇到左括号就进栈
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
            push(top, exp[i]);

        // 如果遇到右括号
        if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}')
        {
            // 若栈空则出错
            if (stackempty(*top))
            {
                cout << "多余右括号" << endl;
                return -1;
            }
            else
            {
                // 判断是否括号匹配
                if ((*top)->data == '(')
                {
                    if (exp[i] == ')')
                        pop(top);
                    else
                    {
                        cout << "左右括号不匹配" << endl;
                        return -1;
                    }
                }
                else if ((*top)->data == '[')
                {
                    if (exp[i] == ']')
                        pop(top);
                    else
                    {
                        cout << "左右括号不匹配" << endl;
                        return -1;
                    }
                }
                else if ((*top)->data == '{')
                {
                    if (exp[i] == '}')
                        pop(top);
                    else
                    {
                        cout << "左右括号不匹配" << endl;
                        return -1;
                    }
                }
            }
        }
    }
    if (stackempty(*top))
    {
        cout << "表达式正确" << endl;
        return -1;
    }
    else
    {
        cout << "多余左括号" << endl;
        return 1;
    }
}

int main()
{
    stacknode *top = (stacknode *)malloc(sizeof(stacknode));
    top = NULL;

    char exp[100];
    cout << "请输入括号表达式:";
    cin >> exp;

    matching(exp, &top);
}
