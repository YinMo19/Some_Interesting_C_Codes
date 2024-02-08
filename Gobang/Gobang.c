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
#include <stddef.h>

point  player_choose;
point  AI_choose;
size_t player_total_score = 0;
size_t AI_total_score     = 0;
bool   is_win             = false;

int main(int argc, char const *argv[]) {

    srand(time(NULL));

    // initial board
    char board[MAX_SIZE][MAX_SIZE] = {0};
    system("clear");

    printf("请输入回车以开始游戏。");

    // main loop
    while (true) {
        __prompt_for_move__("请输入你的落子位置。格式为两个坐标，以空格隔开：",
                            player_choose.x, player_choose.y);
        board[player_choose.x - 1][player_choose.y - 1] = _Player_Occupied_;

        alphabeta best       = {-_INFINITY_, _INFINITY_};
        point     best_point = {0, 0};
        // calc_next(board, 3, best, 1, &best_point);
        board[best_point.x][best_point.y] = _AI_Occupied_;

        if (calc_total_score(board, 1) >= _five_) {
            system("clear");
            print_board(board);
            is_win = true;
            break;
        }

        if (calc_total_score(board, 0) >= _five_) {
            system("clear");
            print_board(board);
            break;
        }
        system("clear");
    }

    printf("%s win!\n", is_win ? "AI" : "Player");
    return 0;
}