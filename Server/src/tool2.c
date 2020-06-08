/*
** EPITECH PROJECT, 2019
** Server
** File description:
** tool2.c
*/

#include <stdlib.h>
#include <time.h>

int get_rand_num(int min, int max, int percent)
{
    int res;
    int act = rand() % 100;
    time_t t;

    if (percent < act)
        return 0;
    if (min > max)
        return min;
    //srand((unsigned) time(&t));
    res = rand() % max;
    while (res <  min)
        res = rand() % max;
    printf("%d \n", res);
    return res;
}