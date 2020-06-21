/*
** EPITECH PROJECT, 2019
** server command
** File description:
** mct.c
*/

#include "command.h"

void mct(int fd_cli, __attribute__((unused))client_t *clis, server_t *server,
__attribute__((unused))char *command)
{
    char *buff = NULL;
    char *res = NULL;
    tile_t *tile;

    buff = malloc(sizeof(char) * MESSAGE_SIZE);
    res = malloc(sizeof(char) * MESSAGE_SIZE);
    if (buff == NULL || res == NULL)
        error("Error : malloc failed\n");
    for (int y = 0; y < server->y; y++) {
        for (int x = 0; x < server->x; x++) {
            tile = &(server->map[y][x]);
            sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n", x, y, tile->q0,
            tile->q1, tile->q2, tile->q3, tile->q4, tile->q5, tile->q6);
            res = str_concat(res, buff);
        }
    }
    send(fd_cli, res, strlen(res), 0);
    free(res);
}
