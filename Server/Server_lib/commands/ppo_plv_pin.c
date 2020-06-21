/*
** EPITECH PROJECT, 2019
** server command
** File description:
** ppo_plv_pin.c
*/

#include "command.h"

void ppo_plv_pin(int fd_cli, client_t *cli, server_t *server, char *command)
{
    char *buff = NULL;
    int nb = -1;

    buff = malloc(sizeof(char) * MESSAGE_SIZE);
    if (buff == NULL)
        error("Error : malloc failed\n");
    nb = atoi(str_breaker(command, ' ', 2, 0));
    if (!cli->ai || !buff)
        return error("Error");
    if (str_in_str("ppo", command))
        sprintf(buff, "ppo %d %d %d %d\n", cli->ai->player_number, cli->ai->x,
        cli->ai->y, cli->ai->orientation);
    if (str_in_str("plv", command))
        sprintf(buff, "plv %d %d\n", cli->ai->player_number, cli->ai->level);
    if (str_in_str("pin", command)) {
        sprintf(buff, "pin %d %d %d %d %d %d %d %d %d %d\n",
        cli->ai->player_number, cli->ai->x, cli->ai->y, cli->ai->invent->q0,
        cli->ai->invent->q1, cli->ai->invent->q2, cli->ai->invent->q3,
        cli->ai->invent->q4, cli->ai->invent->q5, cli->ai->invent->q6);
    }
    send(fd_cli, buff, strlen(buff), 0);
    free(buff);
}
