/*
** EPITECH PROJECT, 2019
** server command
** File description:
** ppo_plv_pin.c
*/

#include "command.h"

void ppo_plv_pin(int fd_cli, client_t *clis, server_t *server, char *command)
{
    char *buff = malloc(70);
    int nb = -1;
    ai_s *ai;

    if (buff == NULL)
        exit(84);
    memset(buff, 0, 70);
    nb = atoi(str_breaker(command, ' ', 2, 0));
    ai = get_ai_by_nb(server, nb);
    if (!ai || !buff)
        return error_s(fd_cli);
    if (str_in_str("ppo", command))
        sprintf(buff, "ppo %d %d %d %d\n", ai->player_number, ai->x
        , ai->y, ai->orientation);
    if (str_in_str("plv", command))
        sprintf(buff, "plv %d %d\n", ai->player_number, ai->level);
    if (str_in_str("pin", command))
        sprintf(buff, "pin %d %d %d %d %d %d %d %d %d %d\n", ai->player_number,
        ai->x, ai->y, ai->invent->q0, ai->invent->q1, ai->invent->q2,
        ai->invent->q3, ai->invent->q4, ai->invent->q5, ai->invent->q6);
    send(fd_cli, buff, strlen(buff), 0);
    if (DEBUG)
        printf("message send : %s\n", buff);
    free(buff);
}
