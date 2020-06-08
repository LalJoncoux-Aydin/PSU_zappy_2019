/*
** EPITECH PROJECT, 2019
** server
** File description:
** server2.c
*/

#include "command.h"
#include "server.h"

void msz(int fd_cli, client_t *clis __attribute__((unused)), server_t *server ,char *command __attribute__((unused)))
{
    char *buff = malloc(20);

    memset(buff, 0, 20);
    sprintf(buff, "msz %d %d\n", server->x, server->y);
    send(fd_cli, buff, strlen(buff), 0);
    if (DEBUG)
        printf("message send : %s",buff);
    free(buff);
}

void bct(int fd_cli, client_t *clis __attribute__((unused)), server_t *server ,char *command)
{
    char *buff = malloc(50);
    int x = atoi(str_breaker(command, ' ', 2, 0)); // ! CHECK
    int y = atoi(str_breaker(command, ' ', 3, 0));
    tile_t *tile = &(server->map[y][x]);

    memset(buff, 0, 50);
    sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n"
    , x, y,tile->q0, tile->q1, tile->q2, tile->q3, tile->q4, tile->q5, tile->q6);
    send(fd_cli, buff, strlen(buff), 0);
    if (DEBUG)
        printf("message send : %s",buff);
    free(buff);
}