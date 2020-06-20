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
    {"Look", look, 1},
};

static void del_cli(client_t **head, int fd)
{
    client_t *temp = *head;
    client_t *prev;

    if (temp != NULL && temp->fd == fd) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->fd != fd) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}

static void manage_message(char *msg, int *tri_force, client_t *clis, server_t *server)
{
    int sender_fd = tri_force[1];

    for (int i = 0; i < NBR_OF_COMMAND; i++) {
        if (str_in_str(commands[i].command, msg)) {
            if (occurrences_of_char(' ', msg) != commands[i].nb_of_arg)
                error_s(clis->fd);
            else
                commands[i].func(sender_fd, clis, server, msg);
        }
    }
}

void manage_client(fd_set *master, server_t *server_v, int i, client_t **head)
{
    int nbytes;
    char buff[256 * 4];

    if ((nbytes = recv(i, buff, sizeof(buff), 0)) <= 0) {
        del_cli(head, i);
        close(i);
        FD_CLR(i, master);
        return;
    }
    buff[nbytes] = '\0';
    printf("msg ressive form %d  : %s\n", i, buff);
    manage_message(buff, tri_force(server_v->server_fd, i, 0), *head, server_v);
}
