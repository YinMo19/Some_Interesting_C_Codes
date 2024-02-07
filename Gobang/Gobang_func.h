/**
 * @file Gobang.c
 * @author YinMo19 (YinMo19@proton.me)
 * @brief 实现五子棋游戏的函数定义以及头文件
 * @version 0.1
 * @date 2024-02-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef __Gobang_func_h__
#define __Gobang_func_h__

// 'O' in ASCII is 79, 'X' in ASCII is88
#define _AI_Occupied_ 88
#define _Player_Occupied_ 79
#define _marked_ 10
#define MAX_SIZE 15

// 定义棋盘的局势
#define _useless_ 0
#define _whole_one_ 1
#define _whole_two_ 10
#define _whole_three_ 1000
#define _one_double_three_ 4000
#define _two_double_three_ 2000
#define _whole_four_ 1000000
#define _five_ 1000000

#define _INFINITY_ 1000000000

/**
 * @brief this macro function needs a \n before using it.
 *
 * @param prompt the prompt message
 * @param point_x
 * @param point_y
 *
 */
#define __prompt_for_move__(prompt, point_x, point_y)                          \
    do {                                                                       \
        scanf("%*[^\n]%*c");                                                   \
        print_board(board);                                                    \
        printf(prompt);                                                        \
    } while (scanf("%d%*c%d", &point_x, &point_y) != 2 || point_x < 1 ||       \
             point_x > 19 || point_y < 1 || point_y > 19 ||                    \
             board[point_x - 1][point_y - 1] != 0);

/**
 * @brief 由于极大极小值搜索在这里的体现只是将alpha和beta的值调整一下
 *        因此将其写成类函数宏以嵌入形式简化。
 *
 * @param alpha
 * @param beta
 * @param compar 由于两次的比较符号不同，因此需要输入比较符号>(<)
 *
 */
#define __alpha_beta_cutting__(alpha, beta, compar)                                \
    do {                                                                           \
                                                                                   \
        /* 选择合适的下一步，并将这一步设定为已经落子*/       \
        choose_next_point(board, role, next);                                      \
        board[next->x][next->y] =                                                  \
            (role == 0) ? _Player_Occupied_ : _AI_Occupied_;                       \
                                                                                   \
        /*迭代下一步，并回溯已经落子的那一步*/                    \
        alphabeta next_best =                                                      \
            calc_next(board, deepth - 1, tmp_best, role ^ 1, best_point);          \
        board[next->x][next->y] = 0;                                               \
                                                                                   \
        /* 判断是否可以剪枝，并且将已经找到的最好位置更新*/ \
        if (next_best.alpha compar tmp_best.beta) {                                \
            tmp_best.beta = next_best.alpha;                                       \
        } else {                                                                   \
            tmp_best.beta = best.beta;                                             \
            break;                                                                 \
        }                                                                          \
    } while (next->x != -1)

typedef struct point {
    int x;
    int y;
} point;

typedef struct alphabeta {
    ssize_t alpha;
    ssize_t beta;
} alphabeta;

extern size_t player_total_score;
extern size_t AI_total_score;

void      print_board(const char board[MAX_SIZE][MAX_SIZE]);
alphabeta calc_next(char board[MAX_SIZE][MAX_SIZE], const int deepth,
                    alphabeta best, const int role, point *const best_point);
size_t calc_total_score(const char board[MAX_SIZE][MAX_SIZE], const int role);
void   choose_next_point(const char board[MAX_SIZE][MAX_SIZE], const int role,
                         point *const next);
void   copy_start_board(const char board[MAX_SIZE][MAX_SIZE],
                        char       tmp_board[MAX_SIZE][MAX_SIZE]);
void max_density_point(const char board[MAX_SIZE][MAX_SIZE], point *const next);
bool is_full(const char board[MAX_SIZE][MAX_SIZE]);
inline _Noreturn void panic(const char msg[]);

#endif