/*
** EPITECH PROJECT, 2019
** server tools
** File description:
** tool.c
*/

#include "tools.h"

void error(char *msg)
{
    printf("%s", msg);
    exit(84);
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
    while (res < min)
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

char *str_breaker(char *line, char delim, int part, int strict)
{
    int pos = 1;
    char *res = malloc(sizeof(char) * strlen(line));
    int j;

    for (int i = 0; line[i]; i++) {
        if (pos == part) {
            for (j = 0; line[i] && line[i] != delim; i++)
                res[j++] = line[i];
            res[j] = '\0';
            if (!line[i] && strict == 1){
                free(res);
                return NULL;
            }
            return res;
        }
        if (line[i] == delim)
            pos++;
    }
    free(res);
    return NULL;
}

int str_in_str(char *needle, char *haystackt)
{
    for (int i = 0; haystackt[i]; i++) {
        for (int y = 0; needle[y] == haystackt[i]; y++) {
            if (needle[y + 1] == '\0')
                return 1;
            if (haystackt[i++] == '\0')
                return 0;
        }
    }
    return 0;
}
