/*
** EPITECH PROJECT, 2019
** server
** File description:
** server2.c
*/
#include <time.h>
#include "command.h"
#include "server.h"

client_t *get_ai_by_nb(server_t *server_v, int nb)
{
    for (client_t *buff = server_v->head; buff; buff = buff->next)
        if ( buff->type == AI && nb == buff->ai->player_number)
            return buff;
    return NULL;
}
//ppo //n X Y O\n ppo #n\n player’s position
void ppo_plv(int fd_cli, client_t *clis  __attribute__((unused)), server_t *server ,char *command)
{
    char *buff = malloc(70);
    int nb = -1;
    client_t *buff_cli;

    memset(buff, 0, 70);
    nb = atoi(str_breaker(command, ' ', 2, 0));
    buff_cli = get_ai_by_nb(server, nb);
    if (!buff_cli)
        return error_s(fd_cli);
    if (str_in_str("ppo", command))
        sprintf(buff, "ppo %d %d %d %d\n", buff_cli->ai->player_number, buff_cli->ai->x
        , buff_cli->ai->y, buff_cli->ai->orientation);
    if (str_in_str("plv", command))
        sprintf(buff, "plv %d %d\n", buff_cli->ai->player_number, buff_cli->ai->level);
    send(fd_cli, buff, strlen(buff), 0);
    if (DEBUG)
        printf("message send : %s",buff);
    free(buff);
}

void mouvement(int fd_cli, client_t *clis  __attribute__((unused)), server_t *server ,char *command)
{
    char *buff = malloc(70);
    int nb = -1;
    client_t *buff_cli;

    memset(buff, 0, 70);
    nb = atoi(str_breaker(command, ' ', 2, 0));
    buff_cli = get_ai_by_nb(server, nb);
    if (!buff_cli)
        return error_s(fd_cli);
    if (str_in_str("Forward", command));
}


//plv //n L\n plv #n\n player’s level
//pin //n X Y q0 q1 q2 q3 q4 q5 q6\n pin #n\n player’s inventory
