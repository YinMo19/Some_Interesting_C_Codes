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
#define _whole_three_ 150
#define _two_double_three_ 700
#define _whole_four_ 5000
#define _five_ 10000000

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
        print_board((const char(*)[MAX_SIZE]) board, player_choose,            \
                    best_point);                                               \
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

#define __alpha_beta_cutting__(alpha, beta, compar)                            \
    do {                                                                       \
        while (true) {                                                         \
                                                                               \
            choose_next_point((const char(*)[MAX_SIZE]) board, role, next,     \
                              tmp_start_board, __range);                       \
            if (next->x == -1) {                                               \
                break;                                                         \
            }                                                                  \
            board[next->x][next->y] =                                          \
                (role == 0) ? _Player_Occupied_ : _AI_Occupied_;               \
                                                                               \
            alpha = calc_next(board, deepth - 1, now_best, role ^ 1,           \
                              tmp_best_point);                                 \
            if (first_time) {                                                  \
                now_best.alpha   = alpha;                                      \
                now_best_point.x = next->x;                                    \
                now_best_point.y = next->y;                                    \
                first_time       = false;                                      \
            }                                                                  \
                                                                               \
            if (alpha compar best.beta) {                                      \
                if (now_best.alpha compar alpha) {                             \
                    now_best.alpha   = alpha;                                  \
                    now_best_point.x = next->x;                                \
                    now_best_point.y = next->y;                                \
                }                                                              \
            } else {                                                           \
                board[next->x][next->y] = 0;                                   \
                now_best.alpha          = best.beta;                           \
                break;                                                         \
            }                                                                  \
                                                                               \
            board[next->x][next->y] = 0;                                       \
        }                                                                      \
    } while (0)

/**
 * @brief 预定义清屏指令
 *
 */
#ifdef __unix__
#ifndef __clean_defined
#define __clean_defined
#define __clean system("clear")
#endif
#endif

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || \
    defined(_WIN64) || defined(_WIN64_)
#ifndef __clean_defined
#define __clean_defined
#define __clean system("cls")
#endif
#endif

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

void print_board(char const board[MAX_SIZE][MAX_SIZE], point const player,
                 point const AI);
__Alp_or_Bet_t calc_next(char board[MAX_SIZE][MAX_SIZE], const int deepth,
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