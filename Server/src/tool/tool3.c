/*
** EPITECH PROJECT, 2019
** Server
** File description:
** tool3.c
*/

#include "client.h"
#include "tools.h"
#include "server.h"

char *tab_to_str(char **tab)
{
    char *res;
    int size = 0;
    int index = 0;

    for (int i = 0; tab[i]; i++)
        size += strlen(tab[i]);
    res = malloc(size + 3);
    for (int y = 0; tab[y]; y++)
        for (int x = 0; tab[y][x]; x++)
            res[index++] = tab[y][x];
    res[index] = '\0';
    return res;
}

char *check_for_player(coor coords, server_t *server_v)
{
    char *buff = malloc(32);

    for (client_t *clis = server_v->head; clis; clis = clis->next)
        if (clis->type == AI && clis->ai->x == coords.x
        && clis->ai->y == coords.y) {
            sprintf(buff, "Player %d here\n", clis->ai->player_number);
            return buff;
        }
    return NULL;
}

int str_in_str(char *needle, char *haystackt)
{
    int i = 0;

    for (int y = 0; haystackt[i] && needle[y] == haystackt[i]; y++) {
        if (needle[y + 1] == '\0')
            return 1;
        if (haystackt[i++] == '\0')
            return 0;
    }
    return 0;
}
