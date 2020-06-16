/*
** EPITECH PROJECT, 2019
** jo
** File description:
** tool.c
*/
#include "tools.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void add_end_file(char *str, char *str_name)
{
    FILE *_file = NULL;

    _file = fopen(str_name, "a");
    fputs(str, _file);
    fputs("\n", _file);
    fclose(_file);
}

void error(char *msg)
{
    printf("%s",msg);
    exit(84);
}

int occurrences_of_char(char c, char *str)
{
    int res = 0;

    for (int i = 0; str[i] ; i++)
        if(str[i] == c)
            res++;
    return res;
}

void send_all(int fd, char *msg)
{
    int ret;
    int bytes = 0;
    int buflen = strlen(msg);
    char *buff = msg;
    int retry = 0;

    while (bytes < buflen)
    {
        retry = 0;
        ret = send(fd, buff + bytes, buflen - bytes, 0);
        if (ret == -1) {
            retry += 1;
            if (retry == 5)
                error("send fail");
            continue;
        }
        bytes += ret;
    }
}

int *tri_force(int a, int b, int c)
{
    int *res = malloc(sizeof(int) * 3);

    res[0] = a;
    res[1] = b;
    res[2] = c;
    return res;
}

int str_in_str(char *needle, char *haystackt)
{
    for (int i = 0; haystackt[i] ; i++) {
        for (int y = 0; needle[y] == haystackt[i]; y++) {
            if (needle[y + 1] == '\0')
                return 1;
            if (haystackt[i++] == '\0')
                return 0;
        }
    }
    return 0;
}

int return_type(char *str)
{
    if (DEBUG)
        printf("CLI of type %s connected\n",
        (!(strlen(str) < 7) && (str[5] == 'a' && str[6] == 'i'))? "AI" : "GRAPHIC");
    if (strlen(str) < 7)
        return -1;
    if (str[5] == 'a' && str[6] == 'i')
        return AI;
    return GRAPHIC;
}


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
