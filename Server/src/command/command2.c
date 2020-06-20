/*
** EPITECH PROJECT, 2019
** server
** File description:
** server2.c
*/
#include <time.h>
#include "command.h"
#include "server.h"

ai_s *get_ai_by_nb(server_t *server_v, int nb)
{
    for (client_t *buff = server_v->head; buff; buff = buff->next)
        if (buff->type == AI && nb == buff->ai->player_number)
            return buff->ai;
    return NULL;
}

char *ppo_plv_pin_parser(char *command, ai_s *ai)
{
    char *buff = malloc(70);

    if (str_in_str("ppo", command))
        sprintf(buff, "ppo %d %d %d %d\n", ai->player_number, ai->x,
        ai->y, ai->orientation);
    if (str_in_str("plv", command))
        sprintf(buff, "plv %d %d\n", ai->player_number, ai->level);
    if (str_in_str("pin", command))
        sprintf(buff, "pin %d %d %d %d %d %d %d %d %d %d\n", ai->player_number,
        ai->x, ai->y, ai->invent->q0, ai->invent->q1, ai->invent->q2,
        ai->invent->q3, ai->invent->q4, ai->invent->q5, ai->invent->q6);
    return buff;
}

void ppo_plv_pin(int fd_cli, client_t *clis __attribute__((unused)),
server_t *server, char *command)
{
    char *buff;
    int nb = atoi(str_breaker(command, ' ', 2, 0));
    ai_s *ai = get_ai_by_nb(server, nb);

    if (!ai)
        return error_s(fd_cli);
    buff = ppo_plv_pin_parser(command, ai);
    send(fd_cli, buff, strlen(buff), 0);
    free(buff);
}

void forward(int fd_cli, client_t *clis,
server_t *server __attribute__((unused)), char *command __attribute__((unused)))
{
    char *buff = malloc(70);
    ai_s *ai = clis->ai;
    int mod_y[5] = {-84, -1, 0, 1, 0};
    int mod_x[5] = {-84, 0, 1, 0, -1};

    memset(buff, 0, 70);
    if (!ai || !buff)
        return error_s(fd_cli);
    ai->x += mod_x[ai->orientation];
    ai->y += mod_y[ai->orientation];
}

void turn(int fd_cli, client_t *clis __attribute__((unused)),
server_t *server __attribute__((unused)), char *command)
{
    char *buff = malloc(70);
    int left = str_in_str("Left", command);
    ai_s *ai = clis->ai;

    memset(buff, 0, 70);
    if (!ai || !buff)
        return error_s(fd_cli);
    switch (ai->orientation) {
    case NORTH:
        ai->orientation = (left ? WEST : EAST);
        break;
    case SOUTH:
        ai->orientation = (!left ? WEST : EAST);
        break;
    case EAST:
        ai->orientation = (left ? NORTH : SOUTH);
        break;
    case WEST:
        ai->orientation = (!left ? NORTH : SOUTH);
        break;
    }
}