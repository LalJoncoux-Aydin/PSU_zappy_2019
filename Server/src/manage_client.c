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
    {"Forward", forward, 0},
    {"Right", turn, 0},
    {"Left", turn, 0},
    {"Look", look, 0},
    {"Take", take, 1},
    {"nbp", nbp, 0},
    {"Fork", fork_cli, 0},
    {"Incantation", elevation, 0},
};

static void manage_message(char *msg, client_t *cli, server_t *server)
{
    client_t *tmp = NULL;
    bool find = false;

    for (int i = 0; i < NBR_OF_COMMAND; i++) {
        if (str_in_str(commands[i].command, msg)) {
            find = true;
            commands[i].func(cli->fd, cli, server, msg);
            return;
        } else if (strncmp(msg, "ppo", 3) == 0 || strncmp(msg, "plv", 3) == 0 ||
        strncmp(msg, "pin", 3) == 0) {
            find = true;
            for (tmp = cli; tmp->prev != NULL; tmp = tmp->prev);
            ppo_plv_pin(cli->fd, tmp, server, msg);
            return;
        }
    }
    if (find == false)
        send(cli->fd, "suc\n", 4, 0);
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
