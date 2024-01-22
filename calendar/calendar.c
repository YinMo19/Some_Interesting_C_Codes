#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_WIDTH 35
#define DAYS_IN_WEEK 7
#define MONTHS_IN_YEAR 12

// some basic digit.
static const char *months[MONTHS_IN_YEAR] = {
    "January", "February", "March",     "April",   "May",      "June",
    "July",    "August",   "September", "October", "November", "December",
};
static const int days_in_month_leap[MONTHS_IN_YEAR] = {
    31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
};
static const int days_in_month_normal[MONTHS_IN_YEAR] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
};

/**
 * @brief fail to open file
 *
 * @param fp
 * @return _Noreturn
 */
static inline _Noreturn void fail_to_open_file(FILE const *const fp) {
    fprintf(stderr, "Fail to open file: %p\n", fp);
    exit(1);
}

/**
 * @brief get the number of days in a month
 *
 * @param year
 * @param month
 * @return int
 */
int days_in_month(int const year, int const month) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return days_in_month_leap[month - 1];
    } else {
        return days_in_month_normal[month - 1];
    }
}

/**
 * @brief calculate the weekday in the first day of year
 *
 * @details https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
 * @param year
 * @return int
 */
int first_weekday_of_year(int const year) {
    int y = year - 1;
    return (y + y / 4 - y / 100 + y / 400 + 1) % 7;
}

/**
 * @brief calculate the weekday in the first day of month
 *
 * @param year
 * @param month
 * @return int
 */
int first_weekday_of_month(int const year, int const month) {
    int first_weekday = first_weekday_of_year(year);
    int days          = first_weekday;

    for (size_t each_month = 1; each_month < month; each_month++) {
        days += days_in_month(year, each_month);
    }
    return days % DAYS_IN_WEEK;
}

/**
 * @brief fill the space for given number
 *
 * @param num
 */
void fill_space(int const num, FILE *const fp) {
    for (int i = 0; i < num; i++) {
        fprintf(fp, " ");
    }
}

/**
 * @brief print the title of calendar
 *
 * @param year
 * @param month
 */
void print_calendar_title(int const year, int const month, FILE *const fp) {
    int month_Width = (int) strlen(months[month - 1]);
    int num_space   = (LINE_WIDTH - month_Width) / 2;

    fill_space(num_space, fp);
    fprintf(fp, "%s\n", months[month - 1]);
    fprintf(fp, "Sun. Mon. Tue. Wed. Thu. Fri. Sat. \n");
}

/**
 * @brief print the content of calendar
 *
 * @param year
 * @param month
 */
void print_calendar_content(int const year, int const month, FILE *const fp) {
    int day  = first_weekday_of_month(year, month);
    int days = days_in_month(year, month);
    fill_space(day * 5, fp);

    for (int i = 1; i <= days; i++) {
        fprintf(fp, "%3d  ", i);
        if ((i + day) % DAYS_IN_WEEK == 0) fprintf(fp, "\n");
    }
    fprintf(fp, "\n");
}

int main() {
    int year = 0;

    // get year and do some validation
    do {
        printf("Input the year: ");
        if (scanf("%d", &year) != 1) scanf("%*[^\n]");
    } while (year <= 0);

    // open file and do some validation
    FILE *fp = fopen("calendar.txt", "w");
    if (fp == NULL) {
        fail_to_open_file(fp);
    }

    // print calendar title
    fill_space(9, fp);
    fprintf(fp, "Calendar of %d\n\n", year);

    // print calendar content
    for (size_t month = 1; month <= MONTHS_IN_YEAR; month++) {
        print_calendar_title(year, month, fp);
        print_calendar_content(year, month, fp);
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}
