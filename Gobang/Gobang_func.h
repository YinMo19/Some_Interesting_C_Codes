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
#include <string.h>
#include <time.h>

#ifndef __Gobang_func_h__
#define __Gobang_func_h__

// 'O' in ASCII is 79, 'X' in ASCII is88
#define _AI_Occupied_ 88
#define _Player_Occupied_ 79
#define _marked_ 10
#define MAX_SIZE 15

// 定义棋盘的局势
#define _whole_two_ 50
#define _whole_three_ 200
#define _two_double_three_ 1000
#define _whole_four_ 50000
#define _five_ 100000000

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
             point_x > MAX_SIZE || point_y < 1 || point_y > MAX_SIZE ||        \
             board[point_x - 1][point_y - 1] != 0);

/**
 * @brief 计算当前局势的得分
 *
 */
#define __score__(occupied)                                                    \
    do {                                                                       \
        for (size_t i = 0; i < MAX_SIZE; i++) {                                \
            for (size_t j = 0; j < MAX_SIZE; j++) {                            \
                if (board[i][j] == occupied) {                                 \
                    for (size_t k = 0; k < 4; k++) {                           \
                        sum += find_score(board, k, i, j, role);               \
                    }                                                          \
                }                                                              \
            }                                                                  \
        }                                                                      \
    } while (0)

// 定义__Alp_or_Bet_t类型
#ifndef __Alp_or_Bet_t_defined
typedef ssize_t __Alp_or_Bet_t;
#define __Alp_or_Bet_t_defined
#endif

typedef struct alphabeta {
    __Alp_or_Bet_t alpha;
    __Alp_or_Bet_t beta;
} alphabeta;

typedef struct point {
    int x;
    int y;
} point;

typedef struct range {
    size_t xmin;
    size_t xmax;
    size_t ymin;
    size_t ymax;
} range;

extern size_t player_total_score;
extern size_t AI_total_score;

void           print_board(const char board[MAX_SIZE][MAX_SIZE]);
__Alp_or_Bet_t calc_next_debug(char board[MAX_SIZE][MAX_SIZE], const int deepth,
                               alphabeta best, const int role,
                               point *const best_point);
size_t calc_total_score(const char board[MAX_SIZE][MAX_SIZE], const int role);
void   choose_next_point(const char board[MAX_SIZE][MAX_SIZE], const int role,
                         point *const next, char tmp_board[MAX_SIZE][MAX_SIZE],
                         range const __range);
void   copy_start_board(const char board[MAX_SIZE][MAX_SIZE],
                        char       tmp_board[MAX_SIZE][MAX_SIZE]);
void max_density_point(const char board[MAX_SIZE][MAX_SIZE], point *const next);
bool is_full(const char board[MAX_SIZE][MAX_SIZE], range const __range);
size_t find_score(const char tmp_board[MAX_SIZE][MAX_SIZE], const size_t dir,
                  const size_t i, const size_t j, const int role);
bool   win_judge(const char board[MAX_SIZE][MAX_SIZE], const int role);
range  calc_range(const char board[MAX_SIZE][MAX_SIZE]);
size_t max(size_t a, size_t b);
size_t min(size_t a, size_t b);

#endif