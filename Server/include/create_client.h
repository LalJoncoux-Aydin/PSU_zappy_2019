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

void create_client(client_t **head, int new_fd, server_t *server_v);

#endif /* CREATE_CLIENT_H_ */
