/**
 * @file card.c
 * @author YinMo19 (YinMo19@proton.me)
 * @brief CARD_GAME:
 * Ask the customer to think of a number, and ask the customer to
 * choose the card with that number among some cards, if you let the organizer
 * know the card that the customer has chosen, then you can know the number that
 * the customer wants
 *
 * @version 1.0
 * @date 2024-01-24
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARD_NUMBER 6
#define MAX_NUMEER_IN_CARDS 63

typedef struct _CARD_ {
    int sum_of_card;
    int sequence_of_card[CARD_NUMBER];
} _CARD_;

/**
 * @brief the cmp_fn for qsort
 *
 * @param a
 * @param b
 * @return int
 */
int cmp_num(const void *a, const void *b) { return *(int *) a - *(int *) b; }

/**
 * @brief add number to card
 *
 * @param card an one dimensional array
 * @param number
 */
void array_append(int card[MAX_NUMEER_IN_CARDS], int number) {
    for (int i = 0; i < MAX_NUMEER_IN_CARDS; i++) {
        if (card[i] == number) {
            return;
        } else if (card[i] == 0) {
            card[i] = number;
            return;
        }
    }
    printf("error!\n");
    exit(1);
}

/**
 * @brief make sum of the card numbers by chosen randomly
 *
 * @param card a two dimensional array
 * @param cnt chosen number of cards.eg. 3 of 6 cards
 * @param _card_ a struct include sum_of_first_card and sequence_of_card
 */
void add_number_to_card_by_chosen(int    card[CARD_NUMBER][MAX_NUMEER_IN_CARDS],
                                  size_t cnt, _CARD_ _card_) {
    if (cnt == 0) {
        return;
    } else {
        for (int i = 0; i < CARD_NUMBER; i++) {
            if (_card_.sequence_of_card[i] == 0) {
                _card_.sum_of_card += card[i][0];
                _card_.sequence_of_card[i] = 1;

                add_number_to_card_by_chosen(card, cnt - 1, _card_);

                for (int j = 0; j < CARD_NUMBER; j++) {
                    // if the card is chosen(sequence_of_card[j] == 1), add the
                    // number to the card.
                    if (_card_.sequence_of_card[j] == 1) {
                        array_append(card[j], _card_.sum_of_card);
                    }
                }

                // reset
                _card_.sequence_of_card[i] = 0;
                _card_.sum_of_card -= card[i][0];
            }
        }
    }
}

/**
 * @brief print space
 *
 * @param number
 */
void print_space(FILE *fp, int number) {
    for (int i = 0; i < number; i++) {
        fprintf(fp, " ");
    }
}

/**
 * @brief print cards
 *
 * @param card
 */
void print_cards(int card[CARD_NUMBER][MAX_NUMEER_IN_CARDS]) {
    // open the file and do some error check
    FILE *fp = fopen("cards.txt", "w");
    if (fp == NULL) {
        printf("error\n");
        exit(1);
    }

    for (int i = 0; i < CARD_NUMBER; i++) {
        // print card title
        print_space(fp, 9);
        fprintf(fp, "card %d \n", i + 1);

        // Judge where to start print
        int r = 0;
        for (r = 0; r < MAX_NUMEER_IN_CARDS; r++) {
            if (card[i][r] != 0) {
                break;
            }
        }

        // print card
        for (int j = r; j < MAX_NUMEER_IN_CARDS; j++) {
            fprintf(fp, "%4d", card[i][j]);
            if ((j + 1 - r) % 6 == 0) {
                fprintf(fp, "\n");
            }
        }
        fprintf(fp, "\n\n");
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    // make card and _card_
    int card[CARD_NUMBER][MAX_NUMEER_IN_CARDS] = {
        {1}, {2}, {4}, {8}, {16}, {32},
    };
    _CARD_ _card_ = {0, {0}};

    // main execution
    add_number_to_card_by_chosen(card, CARD_NUMBER, _card_);
    for (int i = 0; i < CARD_NUMBER; i++) {
        qsort((void *) card[i], MAX_NUMEER_IN_CARDS, sizeof(int), cmp_num);
    }
    print_cards(card);

    // print the time taken
    clock_t end       = clock();
    double  time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_used);
    return 0;
}