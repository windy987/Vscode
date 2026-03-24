// 题目背景
// 你是一名考古学家，正在修复一块记录着远古魔法的“虚空石板”。石板上的文字是一行连续的字符序列。
// 为了修复它，你需要使用一只魔法笔在石板上进行操作。魔法笔有一个光标（Cursor），指示着当前的操作位置。
// 初始时，石板上有一串已有的字符序列（也可能为空），光标位于序列的最前端（即第一个字符之前）。
// 你需要根据指令移动光标，或者在光标处进行修改。
// 指令共有四种：
// 右移（Move Right）：将光标向右移动一个字符的位置。如果光标已经位于最右端（即最后一个字符之后），则忽略此操作。
// 左移（Move Left）：将光标向左移动一个字符的位置。如果光标已经位于最前端，则忽略此操作。
// 刻写（Insert）：在当前光标的左侧插入一个字符
// c。插入后，光标的位置保持在由该字符和它原来的后继字符之间（即光标相对位置不变，但在整个串中的下标增加了）。
// 抹除（Backspace）：删除当前光标左侧的一个字符。如果光标左侧没有字符（即光标在最前端），则忽略此操作。
// 请在完成所有 Q 条指令后，输出石板上最终的字符序列。

// 输入格式
// 第一行包含一个字符串 Sinit，表示石板初始的内容。如果 Sinit 为字符串 "EMPTY"（不含引号），则表示初始为空。
// 第二行包含一个整数 Q，表示指令的数量。
// 接下来 Q 行，每行描述一个指令，格式如下：
// > ：表示右移（Move Right）。
// > < ：表示左移（Move Left）。
// > I c ：表示刻写字符 c（c 是一个小写字母或数字）。
// > D ：表示抹除（Backspace）。
// 输出格式
// 输出一行，表示修复完成后的最终字符串。
// 样例输入
// abc
// 6
// >
// >
// I x
// <
// D
// I y
// 样例输出
// ayxc
// 解释：
// 初始：| a b c （光标在最前，| 表示光标）
// > ：a | b c
// > ：a b | c
// > I x ：a b x | c （在光标左侧插入 x）
// > < ：a b | x c
// > D ：a | x c （删除光标左侧的 b）
// > I y ：a y | x c （在光标左侧插入 y）
// 最终序列：ayxc

#include <bits/stdc++.h>
using namespace std;
int main()
{
    list<char> L;
    string s;
    cin >> s;
    if (s == "EMPTY")
        s = "";
    for (int i = 0; i < s.length(); i++)
        L.push_back(s[i]);
    list<char>::iterator it = L.begin();
    int Q;
    char ins, cha;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        cin >> ins;
        switch (ins)
        {
        case '>':
            if (it == L.end())
                break;
            else
            {
                it++;
                break;
            }
        case '<':
            if (it == L.begin())
                break;
            else
            {
                it--;
                break;
            }
        case 'D':
            if (it == L.begin())
                break;
            else
            {
                it--;
                it = L.erase(it);
                break;
            }
        case 'I':
            cin >> cha;
            L.insert(it, cha);
            break;
        }
    }
    for (list<char>::iterator u = L.begin(); u != L.end(); u++)
    {
        cout << *u;
    }
}