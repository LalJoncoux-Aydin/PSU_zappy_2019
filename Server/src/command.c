/*
** EPITECH PROJECT, 2019
** server
** File description:
** server2.c
*/

#include "command.h"

//void my_send(client_t *cli, char *msg)
//{
//    if (str_breaker(msg, ' ', 4, 0) == NULL)
//        return;
//    for (;cli->prev != NULL; cli = cli->prev);
//    for (;cli->next != NULL; cli = cli->next)
//        if (!strcmp(str_breaker(msg, ' ', 3, 0), cli->id))
//            send(cli->fd, str_breaker(msg, ' ', 4, 0), strlen(str_breaker(msg, ' ', 4, 0)), 0);
//
//}
//
//void cli_logout(client_t *cli, char *msg __attribute__((unused)))
//{
//    if (cli->stade == -1)
//        return;
//    cli->stade = -1;
//}