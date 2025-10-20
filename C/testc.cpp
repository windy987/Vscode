#include <iostream>

#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN + 1];

// 基础
int StrAssign(SString T, const char *cstr); // 复制 C 串到 T
int StrLength(SString S);                   // 直接返回 S[0]

// 模式匹配（任选其一；BF 更快写）
int Index_BF(SString S, SString T, int pos); // 从 pos(>=1) 开始找 T，找到返位置，否则返 0

// 片段编辑（Replace 依赖这两个）
int StrDelete(SString S, int pos, int len);   // 删除 S 中 [pos, pos+len-1]，成功返 1，非法返 0
int StrInsert(SString S, int pos, SString T); // 在 pos 前插入 T，可能发生截断；成功返 1，非法返 0

// 目标接口（本实验要交的功能）
int Replace(SString S, SString T, SString V); // 将 S 中所有与 T 相等且不重叠的子串替换为 V，返回替换次数
