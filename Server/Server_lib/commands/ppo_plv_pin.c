/*
** EPITECH PROJECT, 2019
** server command
** File description:
** ppo_plv_pin.c
*/

#include "command.h"

static void get_sub_commands(char *command, client_t *cli, int fd_cli)
{
    char *buff = NULL;

    buff = malloc(sizeof(char) * MESSAGE_SIZE);
    if (buff == NULL)
        error("Error : malloc failed\n");
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

void ppo_plv_pin(int fd_cli, client_t *cli,
__attribute__((unused))server_t *server, char *command)
{
    client_t *tmp = NULL;
    int nb = -1;
    int i = 0;
    bool _find = false;

    nb = atoi(str_breaker(command, ' ', 2, 0));
    for (tmp = cli; tmp; tmp = tmp->next, i++) {
        if (i == nb) {
            get_sub_commands(command, tmp, fd_cli);
            _find = true;
        }
    }
    if (_find == false)
        send(fd_cli, "ko\n", 3, 0);
    free(tmp);
}
