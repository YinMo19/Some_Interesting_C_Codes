/**
 * @file Gobang.c
 * @author YinMo19 (YinMo19@proton.me)
 * @brief 实现五子棋游戏的函数
 * @version 0.1
 * @date 2024-02-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Gobang_func.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 移动方向
static const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
static const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// 棋局判定
static const char live_five[]      = "11111";
static const char live_four[]      = " 1111 ";
static const char dead_four_A1[]   = " 1111";
static const char dead_four_A2[]   = "1111 ";
static const char dead_four_B1[]   = "111 1";
static const char dead_four_B2[]   = "1 111";
static const char dead_four_C[]    = "11 11";
static const char live_three[]     = " 111 ";
static const char dead_three_A_1[] = "111  ";
static const char dead_three_A_2[] = "  111";
static const char dead_three_B_1[] = " 1 11 ";
static const char dead_three_B_2[] = " 11 1 ";
static const char dead_three_C_1[] = "1  11";
static const char dead_three_C_2[] = "11  1";
static const char dead_three_D[]   = "1 1 1";
static const char live_two[]       = "   11   ";
static const char dead_two_A_1[]   = "   11";
static const char dead_two_A_2[]   = "11   ";
static const char dead_two_B[]     = "  1 1  ";
static const char dead_two_C[]     = " 1  1 ";

/**
 * @brief 将棋盘打印出来
 *
 * @param board
 */
void print_board(const char board[MAX_SIZE][MAX_SIZE]) {
    printf("  ");
    for (size_t i = 0; i < MAX_SIZE; i++) {
        printf("%2zu ", i + 1);
    }
    printf("\n");

    for (size_t i = 0; i < MAX_SIZE; i++) {
        printf("%2zu ", i + 1);
        for (size_t j = 0; j < MAX_SIZE; j++) {
            if (board[i][j] == 0) {
                printf("*  ");
            } else {
                printf("%c  ", board[i][j]);
            }
        }
        printf("\n");
    }
    printf("您的棋子为O，电脑的棋子为X,未落子的则为*\n");
}

/**
 * @brief 遍历每一个可能场景，计算最优策略
 *
 * @param board
 * @param deepth 迭代深度,初次传入时必须是奇数
 * @return alphabeta 函数的返回值是alpha-beta剪枝搜索所得到的alpha-beta值
 */
alphabeta calc_next(char board[MAX_SIZE][MAX_SIZE], const int deepth,
                    alphabeta best, const int role,
                    point *const restrict best_point) {

    // 如果迭代深度为0，(即此时达到迭代的底层)则计算此时的局势
    // 局势的计算方式为role代表方的总分减去role的对方的总分
    // 这样的到的局势值就是alpha-beta剪枝搜索的最底层alpha or beta值
    if (deepth == 1) {
        if (role == 1) {
            best.beta = (ssize_t) calc_total_score(board, role) -
                        (ssize_t) calc_total_score(board, role ^ 1);
        } else {
            best.alpha = (ssize_t) calc_total_score(board, role) -
                         (ssize_t) calc_total_score(board, role ^ 1);
        }

        return best;
    }

    // 初始化next的x值为-1。
    // 需要注意的点：我们的best每次循环都会修改，所以需要一个临时变量
    // 一旦发现这个分支是不合理的，我们就会用best重新赋值给
    // tmp_best，这样就可以保证alpha-beta剪枝是正确的
    point *next              = malloc(sizeof(point));
    next->x                  = -1;
    alphabeta tmp_best       = best;
    point    *tmp_best_point = malloc(sizeof(point));

    // 可复用的类函数宏__alpha_beta_cutting__
    // 被定义在Gobang_func.h中
    if (role == 1) {
        __alpha_beta_cutting__(alpha, beta, <);
    } else {
        __alpha_beta_cutting__(alpha, beta, >);
    }

    // 给搜索到的最优策略赋值
    best_point->x = tmp_best_point->x;
    best_point->y = tmp_best_point->y;

    // 释放next、tmp_best_point指针，返回alpha-beta剪枝搜索的alpha-beta值
    free(next);
    free(tmp_best_point);
    return tmp_best;
}

/**
 * @brief 计算玩家或者AI的的成绩
 *
 * @details 计分的评判机制
 *          1.活四即已经胜利，这种局面和胜利相同
 *          2.被堵一侧的四和活三相同，即同样是_whole_three_的分数
 *          3.所有两侧都被堵的均记为0分，即无效
 *          4.双三（没有被堵）即胜利，而被堵一处则可以进行两次冲四，记4000分
 *          5.双四（被堵两处）即胜利
 *
 * @param board
 * @param role 0或者1，表示AI或者玩家
 * @return size_t 返回role对应的成绩
 */
size_t calc_total_score(const char board[MAX_SIZE][MAX_SIZE], const int role) {
    size_t sum = 0;

    if (role == 1) {
        __score__(_AI_Occupied_);
    } else {
        __score__(_Player_Occupied_);
    }
    return sum;
}

/**
 * @brief 选择一个比较大可能的落子点，增强alpha-beta剪枝的高效
 *
 * @param board
 * @param role
 * @param next 初始传入空指针，再无法找到下一个点时返回x坐标值为-1
 * @return point
 */
void choose_next_point(const char board[MAX_SIZE][MAX_SIZE], const int role,
                       point *const restrict next) {

    // 静态的棋盘，每次搜索之后标记位置。
    static char tmp_start_board[MAX_SIZE][MAX_SIZE] = {0};

    // 如果传入指针为空指针，那么意味着这是第一次调用
    // 寻找密度最大的点作为起始点
    if (next->x == -1) {
        copy_start_board(board, tmp_start_board);
        max_density_point(board, next);
        tmp_start_board[next->x][next->y] = _marked_;
        return;
    }

    // 如果传入指针不为空指针，那么意味着这是第二次(及以上)调用
    // 我们将临时的next设置为上一个next值（随机选择的）周围的点，
    // 如果那个点不是可以选择的（可能是数组越界或者已经被标记）
    // 则继续循环的20次寻找直到搜寻到一个可以选择的点。
    int   search_cnt = 0;
    point tmp_next   = {0, 0};
    while (search_cnt++ < 20) {
        int random = rand() % 8;
        tmp_next.x = next->x + dx[random];
        tmp_next.y = next->y + dy[random];
        if (tmp_next.x < 0 || tmp_next.x >= MAX_SIZE || tmp_next.y < 0 ||
            tmp_next.y >= MAX_SIZE) {
            continue;
        }

        // 此时的next点可能是不可选择的不会让数组越界的点
        next->x = tmp_next.x;
        next->y = tmp_next.y;
        if (tmp_start_board[tmp_next.x][tmp_next.y] == 0) {
            tmp_start_board[tmp_next.x][tmp_next.y] = _marked_;
            return;
        }
    }

    //假如20次都没找到可以选择的点
    // 先判断是否已经搜索结束
    if (is_full(board)) {
        next->x = -1;
    }

    // 否则从头找到一个可以选择的点
    else {
        int address = 0;
        while (address++ < MAX_SIZE * MAX_SIZE) {
            if (tmp_start_board[address / MAX_SIZE][address % MAX_SIZE] == 0) {
                next->x = address / MAX_SIZE;
                next->y = address % MAX_SIZE;
                return;
            }
        }
    }
}

/**
 * @brief 将棋盘复制到临时棋盘
 *
 * @param board
 * @param tmp_board
 */
void copy_start_board(const char board[MAX_SIZE][MAX_SIZE],
                      char       tmp_board[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            tmp_board[i][j] = board[i][j];
        }
    };
}

/**
 * @brief 寻找最大密度点作为一轮搜索的起点
 *
 * @param board
 * @param next
 */
void max_density_point(const char board[MAX_SIZE][MAX_SIZE],
                       point *const restrict next) {

    // 设置密度的定义是空格周围8个位置中非空数量，
    // 我们设置最大密度对应的点为next，即搜索起点
    int max_density     = 0;
    int tmp_max_density = 0;
    for (size_t i = 1; i < MAX_SIZE - 1; i++) {
        for (size_t j = 1; j < MAX_SIZE - 1; j++) {
            if (board[i][j] == 0) {
                tmp_max_density = board[i - 1][j - 1] + board[i - 1][j] +
                                  board[i - 1][j + 1] + board[i][j - 1] +
                                  board[i][j + 1] + board[i + 1][j - 1] +
                                  board[i + 1][j] + board[i + 1][j + 1];
                if (tmp_max_density > max_density) {
                    max_density = tmp_max_density;
                    next->x     = i;
                    next->y     = j;
                }
                if (max_density == 8) {
                    break;
                }
            }
        }
    }
}

/**
 * @brief 判断棋盘是否已经满了
 *
 * @param board
 * @return true
 * @return false
 */
bool is_full(const char board[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief 从一个点向四周寻找，返回分数。
 *
 * @details 提前定义好各种情况，然后使用strstr寻炸是否存在子串。
 *
 * @param board
 * @param dir
 * @param i
 * @param j
 * @param role
 */
size_t find_score(const char board[MAX_SIZE][MAX_SIZE], const size_t dir,
                  const size_t i, const size_t j, const int role) {
    char line[10] = {0};
    memset(line, ' ', 10);

    // 把特定方向上的点拿出来，将空白设为0，与role对应的设为1，对方则是0.
    for (int k = -4; k < 5; k++) {
        if (i + k * dx[dir] < 0 || i + k * dx[dir] >= MAX_SIZE ||
            j + k * dy[dir] < 0 || j + k * dy[dir] >= MAX_SIZE) {
            continue;
        }
        line[5 + k] = (board[i + k * dx[dir]][j + k * dy[dir]] == 0)
                          ? ' '
                          : (board[i + k * dx[dir]][j + k * dy[dir]] ==
                             _Player_Occupied_) ^
                                role + '0';
    }

    // 将其与之前设置的各种棋局进行比较
    if (strstr(line, live_five) != NULL) {
        return _five_;
    } else if (strstr(line, live_five) != NULL) {
        return _whole_four_;
    } else if (strstr(line, dead_four_A1) != NULL ||
               strstr(line, dead_four_A2) != NULL ||
               strstr(line, dead_four_B1) != NULL ||
               strstr(line, dead_four_B2) != NULL ||
               strstr(line, dead_four_C) != NULL ||
               strstr(line, live_three) != NULL) {
        return _two_double_three_;
    } else if (strstr(line, dead_three_A_1) != NULL ||
               strstr(line, dead_three_A_2) != NULL ||
               strstr(line, dead_three_B_1) != NULL ||
               strstr(line, dead_three_B_2) != NULL ||
               strstr(line, dead_three_C_1) != NULL ||
               strstr(line, dead_three_C_2) != NULL ||
               strstr(line, dead_three_D) != NULL ||
               strstr(line, live_two) != NULL) {
        return _whole_three_;
    } else if (strstr(line, dead_two_A_1) != NULL ||
               strstr(line, dead_two_A_2) != NULL ||
               strstr(line, dead_two_B) != NULL ||
               strstr(line, dead_two_C) != NULL) {
        return _whole_two_;
    }
    return 0;
}