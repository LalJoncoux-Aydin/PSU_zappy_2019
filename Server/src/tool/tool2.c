/*
** EPITECH PROJECT, 2019
** Server
** File description:
** tool2.c
*/
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

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

char *str_concat(char *con, char *cat)
{

    if (!con || !cat)
        return NULL;
    con = realloc(con, strlen(con) + strlen(cat) + 1);
    if (!con)
        return NULL;
    return strcat(con, cat);
}

int return_type(char *str)
{
    if (DEBUG)
        printf("CLI of type %s connected (msg recv : %s\n",
        (!(strlen(str) < 7) && (str[5] == 'a' && str[6] == 'i'))
        ? "AI" : "GRAPHIC", str);
    if (strlen(str) < 7)
        return -1;
    if (str[5] == 'a' && str[6] == 'i')
        return AI;
    return GRAPHIC;
}

int eq_str(char *str1, char *str2)
{
    for (int i = 0; str1[i] && str2[i]; i++)
        if (str1[i] != str2[i])
            return 0;
    return 1;
}
