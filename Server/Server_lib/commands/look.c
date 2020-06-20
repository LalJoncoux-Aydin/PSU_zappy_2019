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
    printf("player");
    for (int i = cell->q0; i > 0; i--)
        printf(", food");
    for (int i = cell->q1; i > 0; i--)
        printf(", linemate");
    for (int i = cell->q2; i > 0; i--)
        printf(", deraumere");
    for (int i = cell->q3; i > 0; i--)
        printf(", sibur");
    for (int i = cell->q4; i > 0; i--)
        printf(", mendiane");
    for (int i = cell->q5; i > 0; i--)
        printf(", phiras");
    for (int i = cell->q6; i > 0; i--)
        printf(", thystame");
}
//
// static void wring_send()
// {
//
// }

void look(int fd_cli, client_t *clis, server_t *server,
__attribute__((unused)) char *command)
{
    char buff[MESSAGE_SIZE];

    printf("Look");
	// X Y cli --> Pos ia
	// X Y server --> Max size
    for (int y = 0; y < server->y; y++) {
        for (int x = 0; x < server->x; x++) {
            writing_element(&server->map[y][x]);
            // tile = &(server->map[y][x]);
            // sprintf(buff, "bct %d %d %d %d %d %d %d %d %d\n", x, y, tile->q0,
            // tile->q1, tile->q2, tile->q3, tile->q4, tile->q5, tile->q6);
            // res = str_concat(res, buff);
        }
    }
//    send(fd_cli, buff, strlen(buff), 0);
}
