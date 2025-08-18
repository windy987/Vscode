#include <stdio.h>
#include <string.h> // For memset

// 全局变量来跟踪列和对角线的使用情况
// 使用 int 类型代替 bool: 0 表示 false (未使用), 1 表示 true (已使用)
int col_used[8];
int diag1_used[15]; // 主对角线: r - c + 7 (范围 0-14)
int diag2_used[15]; // 副对角线: r + c (范围 0-14)

// 标记某一行是否已经有预置的皇后
// 0 表示该行没有预置皇后, 1 表示有
int row_has_initial_queen[8];

int solution_count; // 合法摆法的计数器

// 回溯函数，尝试在第 r 行放置皇后
void solve(int r) {
    // 基本情况：如果已经成功处理完所有8行 (0到7)
    if (r == 8) {
        solution_count++; // 找到一个完整的合法摆法
        return;
    }

    // 如果当前行 r 已经有预置的皇后 (值为1)
    if (row_has_initial_queen[r] == 1) {
        solve(r + 1); // 直接处理下一行
        return;
    }

    // 否则，尝试在当前空行 r 的每一列 c 放置新的皇后
    for (int c = 0; c < 8; ++c) {
        // 检查位置 (r, c) 是否安全
        // 如果对应标记为0 (false)，则表示安全
        if (col_used[c] == 0 &&
            diag1_used[r - c + 7] == 0 &&
            diag2_used[r + c] == 0) {

            // 放置皇后：将标记设为1 (true)
            col_used[c] = 1;
            diag1_used[r - c + 7] = 1;
            diag2_used[r + c] = 1;

            // 递归处理下一行
            solve(r + 1);

            // 回溯：撤销放置，将标记恢复为0 (false)
            col_used[c] = 0;
            diag1_used[r - c + 7] = 0;
            diag2_used[r + c] = 0;
        }
    }
}

int main() {
    // 初始化所有标记数组为 0 (false)
    memset(col_used, 0, sizeof(col_used));
    memset(diag1_used, 0, sizeof(diag1_used));
    memset(diag2_used, 0, sizeof(diag2_used));
    memset(row_has_initial_queen, 0, sizeof(row_has_initial_queen));
    solution_count = 0;

    int initial_board_cell;

    // 读取棋盘初始状态
    for (int i = 0; i < 8; ++i) { // 行
        for (int j = 0; j < 8; ++j) { // 列
            scanf("%d", &initial_board_cell);
            if (initial_board_cell == 1) {
                // 记录预置皇后的信息
                row_has_initial_queen[i] = 1; // 标记此行有预置皇后
                
                // 标记被占用的列和对角线 (设为1)
                // 题目保证预置的皇后之间不冲突
                col_used[j] = 1;
                diag1_used[i - j + 7] = 1;
                diag2_used[i + j] = 1;
            }
        }
    }

    // 从第0行开始解决问题
    solve(0);

    // 输出结果
    printf("%d\n", solution_count);

    return 0;
}
