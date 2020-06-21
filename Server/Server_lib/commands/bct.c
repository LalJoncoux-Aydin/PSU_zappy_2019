/*
** EPITECH PROJECT, 2019
** server command
** File description:
** bct.c
*/

#include "command.h"

void bct(int fd_cli, __attribute__((unused))client_t *clis, server_t *server,
char *command)
{
    char *buff = malloc(50);
    int x = atoi(str_breaker(command, ' ', 2, 0));
    int y = atoi(str_breaker(command, ' ', 3, 0));
    tile_t *tile;

    if (x < 0 || x > server->x || y < 0 || y > server->y || !buff)
        return error("Error");
    memset(buff, 0, 50);
    tile = &(server->map[y][x]);
    sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
    tile->q0, tile->q1, tile->q2, tile->q3, tile->q4, tile->q5, tile->q6);
    send(fd_cli, buff, strlen(buff), 0);
    if (DEBUG)
        printf("message send : %s", buff);
    free(buff);
}
