/*
** EPITECH PROJECT, 2019
** server
** File description:
** create_client.h
*/

#ifndef CREATE_CLIENT_H_
#define CREATE_CLIENT_H_

#include <stdbool.h>
#include <stdlib.h>

#include "server_struct.h"
#include "tools.h"
#include "command.h"

void send_player_info(client_t *cli);
void get_team_name(client_t *cli, server_t *server_v);
client_t *create_client(int new_fd, server_t *server_v);

#endif /* CREATE_CLIENT_H_ */
