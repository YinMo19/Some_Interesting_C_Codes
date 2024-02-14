/**
 * @file Gobang.c
 * @author YinMo19 (YinMo19@proton.me)
 * @brief 实现一个五子棋游戏
 * @version 0.1
 * @date 2024-02-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Gobang_func.h"
#include <stdio.h>

// #pragma GCC optimize("Ofast")

point     player_choose;
size_t    player_total_score = 0;
size_t    AI_total_score     = 0;
bool      is_win             = false;
alphabeta best               = {-_INFINITY_, _INFINITY_};
point     best_point         = {-1, -1};

int main(int argc, char const *argv[]) {

    srand(time(NULL));

    while (true) {
        // initial board
        char board[MAX_SIZE][MAX_SIZE] = {0};
        int  is_begin                  = 0;
        bool is_first_time             = true;
        __clean;

        printf("您是否先手？是输入1，否则输入0:");
        scanf("%d", &is_begin);
        if (is_begin == 0) {
            board[MAX_SIZE / 2 - 1][MAX_SIZE / 2 - 1] = _AI_Occupied_;
        }

        // main loop
        while (true) {

            // 让用户输入选定的位置并作一定的错误处理
            // 将棋盘上该点设为玩家占据的位置
            __prompt_for_move__(
                "请输入你的落子位置。格式为两个坐标，以空格隔开：（"
                "先横坐标后纵坐标）",
                player_choose.x, player_choose.y);
            board[player_choose.x - 1][player_choose.y - 1] = _Player_Occupied_;

            // 判断是否获胜
            if (win_judge((const char(*)[MAX_SIZE]) board, 0)) {
                __clean;
                print_board((const char(*)[MAX_SIZE]) board, player_choose,
                            best_point);
                break;
            }

            if (is_first_time && is_begin) {
                board[player_choose.x][player_choose.y] = _AI_Occupied_;
                is_first_time                           = false;
                __clean;
                continue;
            }

            // 给出alphabeta剪枝函数和一些变量
            calc_next(board, 4, best, 1, &best_point);
            board[best_point.x][best_point.y] = _AI_Occupied_;

            // 判断是否获胜
            if (win_judge((const char(*)[MAX_SIZE]) board, 1)) {
                __clean;
                print_board((const char(*)[MAX_SIZE]) board, player_choose,
                            best_point);
                is_win = true;
                break;
            }

            // 清屏
            __clean;
        }

        printf("%s win!\n", is_win ? "AI" : "Player");

        // 继续游戏
        int is_continue = 0;
        printf("是否重新游戏？是输入1，否则输入0:");
        scanf("%d", &is_continue);

        if (is_begin == 1) {
            continue;
        } else {
            break;
        }
    }

    return 0;
}