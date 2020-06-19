/*
** EPITECH PROJECT, 2019
** server
** File description:
** server2.c
*/
#include "command.h"

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
    int x = atoi(str_breaker(command, ' ', 2, 0)); // ! CHECK if 0 < && > server->X
    int y = atoi(str_breaker(command, ' ', 3, 0));
    tile_t *tile;// = &(server->map[y][x]);

    if (x < 0 || x > server->x || y < 0 || y > server->y || !buff)
        return error_s(fd_cli);
    memset(buff, 0, 50);
    tile = &(server->map[y][x]);
    sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n"
    , x, y,tile->q0, tile->q1, tile->q2, tile->q3, tile->q4, tile->q5, tile->q6);
    send(fd_cli, buff, strlen(buff), 0);
    if (DEBUG)
        printf("message send : %s",buff);
    free(buff);
}


void mct(int fd_cli, client_t *clis __attribute__((unused)), server_t *server ,char *command  __attribute__((unused)))
{
    char *buff = malloc(50);
    char *res = malloc(50);
    tile_t *tile;// = &(server->map[y][x]);

    memset(buff, 0, 50);
    memset(res, 0, 50);
    for (int y = 0; y < server->y; y++)
        for (int x = 0; x < server->x; x++) {
            tile = &(server->map[y][x]);
            sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n"
            , x, y,tile->q0, tile->q1, tile->q2, tile->q3, tile->q4, tile->q5, tile->q6);
            res = str_concat(res, buff);
        }
    if (DEBUG)
        printf("message send : %s",res);
    send(fd_cli, res, strlen(res), 0);
    free(res);
}

void tna(int fd_cli, client_t *none __attribute__((unused)), server_t *server ,char *none_c  __attribute__((unused)))
{
    char *buff = malloc(50);

    for (int y = 0; server->teams_name[y]; y++) {
            memset(buff, 0, 50);
            sprintf(buff, "tna %s\n", server->teams_name[y]);
            send(fd_cli, buff, strlen(buff), 0);
            if (DEBUG)
                printf("message send : %s",buff);
    }
    free(buff);
}

void pnw(client_t *cli)
{
    char *buff = malloc(50);

    memset(buff, 0, 50);
    sprintf(buff, "pnw %d %d %d %d %d %s\n", cli->ai->player_number,
    cli->ai->x, cli->ai->y, cli->ai->orientation, cli->ai->level, cli->ai->team);
    if (DEBUG)
        printf("%s",buff);
    //struct timespec tim, tim2;
    //tim.tv_sec = 1;
    //tim.tv_nsec = 500;
    //nanosleep(&tim , &tim2);
    for (; cli->prev ; cli = cli->prev);
    for (; cli ; cli = cli->next)
        send(cli->fd, buff, strlen(buff), 0);
}
