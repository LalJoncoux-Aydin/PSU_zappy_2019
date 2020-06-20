/*
** EPITECH PROJECT, 2019
** PSU_tetris_2018
** File description:
** str_breaker.c
*/

#include <stdlib.h>
#include <string.h>
#include "tools.h"

char *str_breaker(char *line, char delim, int part, int strict)
{
    int pos = 1;
    char *res = malloc(sizeof(char) * strlen(line));
    int j;

    for (int i = 0; line[i] ; i++) {
        if (pos == part){
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
