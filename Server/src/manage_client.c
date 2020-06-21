/*
** EPITECH PROJECT, 2019
** server
** File description:
** manage_client.c
*/

#include "manage_client.h"

const command_manager_t commands[NBR_OF_COMMAND] = {
    {"msz", msz, 0},
    {"bct", bct, 2},
    {"mct", mct, 0},
    {"tna", tna, 0},
    {"ppo", ppo_plv_pin, 1},
    {"plv", ppo_plv_pin, 1},
    {"pin", ppo_plv_pin, 1},
    {"Forward", forward, 1},
    {"Right", turn, 1},
    {"Left", turn, 1},
    {"Look", look, 0},
    {"Take", take, 1},
    {"nbp", nbp, 0},
};

static void manage_message(char *msg, client_t *cli, server_t *server)
{
    for (int i = 0; i < NBR_OF_COMMAND; i++) {
        if (str_in_str(commands[i].command, msg)) {
            commands[i].func(cli->fd, cli, server, msg);
        }
    }
}

void manage_client(client_t *cli, server_t *server_v)
{
    int nbytes;
    char buff[MESSAGE_SIZE];

    nbytes = recv(cli->fd, buff, sizeof(buff), MSG_DONTWAIT);
    if (nbytes == -1)
        return;
    buff[nbytes] = '\0';
    printf("msg ressive form %d  : %s\r", cli->fd, buff);
    manage_message(buff, cli, server_v);
}
