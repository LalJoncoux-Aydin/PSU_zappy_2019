/*
** EPITECH PROJECT, 2019
** server
** File description:
** create_client.c
*/

#include "create_client.h"

void send_player_info(client_t *cli)
{
    char size_map[MESSAGE_SIZE];

    sprintf(size_map, "%d\n%d %d\n", NB_CLIENT, cli->x, cli->y);
    send(cli->fd, size_map, strlen(size_map), 0);
}

void get_team_name(client_t *cli, server_t *server_v)
{
    char *team = NULL;

    team = malloc((sizeof(char) * 50));
    if (team == NULL)
        error("Error : malloc failed\n");
    send(cli->fd, "WELCOME\n", 8, 0);
    recv(cli->fd, team, 50, 0);
    for (int i = 0; server_v->teams_name[i] != NULL; i++) {
        if (strcmp(server_v->teams_name[i], team)) {
            cli->team = strdup(team);
        }
    }
    if (strncmp(team, "GRAPHIQUE\n", 9) == 0) {
        cli->type = true;
        free(team);
        return;
    }
    cli->type = false;
    if (cli->team == NULL)
        error("Wrong team name\n");
    send_player_info(cli);
    free(team);
}
