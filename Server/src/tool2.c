/*
** EPITECH PROJECT, 2019
** Server
** File description:
** tool2.c
*/
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

void error_s(int fd)
{
    char *msg = strdup("ko\n");
    send(fd , msg, strlen(msg), 0);
    free(msg);
}

int get_rand_num(int min, int max, int percent)
{
    int res;
    int act = (rand() % 100);

    if (percent < act)
        return 0;
    if (min > max)
        return min;
    res = rand() % max;
    while (res <  min)
        res = rand() % max;
    return res;
}