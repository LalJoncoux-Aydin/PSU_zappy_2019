/*
** EPITECH PROJECT, 2019
** server command
** File description:
** look.c
*/

#include "command.h"

static void writing_element(tile_t *cell)
{
    // If player
    printf("player\n");
    for (int i = cell->q0; i > 0; i--)
        printf(", food\n");
    for (int i = cell->q1; i > 0; i--)
        printf(", linemate\n");
    for (int i = cell->q2; i > 0; i--)
        printf(", deraumere\n");
    for (int i = cell->q3; i > 0; i--)
        printf(", sibur\n");
    for (int i = cell->q4; i > 0; i--)
        printf(", mendiane\n");
    for (int i = cell->q5; i > 0; i--)
        printf(", phiras\n");
    for (int i = cell->q6; i > 0; i--)
        printf(", thystame\n");
}
//
// static void wring_send()
// {
//
// }

void look(int fd_cli, client_t *clis, server_t *server,
__attribute__((unused)) char *command)
{
//    char buff[MESSAGE_SIZE];

    printf("Look\n");
    printf("ai y = %d\n", clis->fd);
//    printf("ai y = %d\n", clis->ai->x);
//    writing_element(&server->map[clis->ai->y][clis->ai->x]);
}
