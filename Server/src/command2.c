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
        if ( buff->type == AI )
            for (ai_s *buff_ai = buff->ai; buff_ai; buff_ai = buff_ai->next)
                if (nb == buff_ai->player_number)
                    return buff_ai;
    return NULL;
}
//ppo //n X Y O\n ppo #n\n player’s position
void ppo_plv_pin(int fd_cli, client_t *clis  __attribute__((unused)), server_t *server ,char *command)
{
    char *buff = malloc(70);
    int nb = -1;
    ai_s *ai;

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
        sprintf(buff, "pin %d %d %d %d %d %d %d %d %d %d\n"
    , ai->player_number, ai->x, ai->y, ai->invent->q0, ai->invent->q1, ai->invent->q2, ai->invent->q3, ai->invent->q4, ai->invent->q5, ai->invent->q6);
    send(fd_cli, buff, strlen(buff), 0);
    if (DEBUG)
        printf("message send : %s",buff);
    free(buff);
}

void forward(int fd_cli, client_t *clis  __attribute__((unused)), server_t *server ,char *command)
{
    char *buff = malloc(70);
    int nb = -1;
    ai_s *ai;

    memset(buff, 0, 70);
    nb = atoi(str_breaker(command, ' ', 2, 0));
    ai = get_ai_by_nb(server, nb);
    if (!ai || !buff)
        return error_s(fd_cli);
    switch (ai->orientation) {
        case NORTH :
        if (ai->y > 0)
            ai->y -= 1;
        break;
        case SOUTH :
        if (ai->y < server->y)
            ai->y += 1;
        break;
        case EAST :
        if (ai->x < server->x)
            ai->x += 1;
        break;
        case WEST :
        if (ai->x > 0)
            ai->x -= 1;
        break;
    }
}


void turn(int fd_cli, client_t *clis  __attribute__((unused)), server_t *server ,char *command)
{
    char *buff = malloc(70);
    int nb = -1;
    int left = str_in_str("Left", command);
    ai_s *ai;

    memset(buff, 0, 70);
    nb = atoi(str_breaker(command, ' ', 2, 0));
    ai = get_ai_by_nb(server, nb);
    if (!ai || !buff)
        return error_s(fd_cli);
    switch (ai->orientation) {
        case NORTH :
        ai->orientation = (left ? WEST : EAST);
        break;
        case SOUTH :
        ai->orientation = (!left ? WEST : EAST);
        break;
        case EAST :
        ai->orientation = (left ? NORTH : SOUTH);
        break;
        case WEST :
        ai->orientation = (!left ? NORTH : SOUTH);
        break;
    }
}

//plv //n L\n plv #n\n player’s level
//pin //n X Y q0 q1 q2 q3 q4 q5 q6\n pin #n\n player’s inventory
