/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** is_dead
*/

#include <time.h>
#include "command.h"

void init_client_time_stamp(client_t *cli)
{
    //! type de return => long int creation_time_stamp
    // cli->creation_time_stamp = time(NULL);
}

void is_dead(int fd_cli, client_t *cli, server_t *server, char *command)
{
    int frequence = server->freq;
    int time_sruvive = 1260 / frequence;

    // if ((time(NULL) - cli->creation_time_stamp - time_sruvive) < 0) {
    //     close(cli->fd);
    //     return (true);
    // }
    return (false);
}