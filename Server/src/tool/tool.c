/*
** EPITECH PROJECT, 2019
** jo
** File description:
** tool.c
*/
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
    printf("%s", msg);
    exit(84);
}

int occurrences_of_char(char c, char *str)
{
    int res = 0;

    for (int i = 0; str[i] ; i++)
        if (str[i] == c)
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