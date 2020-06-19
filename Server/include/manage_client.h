/*
** EPITECH PROJECT, 2019
** server
** File description:
** manage_client.h
*/

#ifndef MANAGE_CLIENTT_H_
#define MANAGE_CLIENT_H_

#include "command.h"

void manage_client(client_t **head, server_t *server_v, int i, fd_set *master);

#endif /* MANAGE_CLIENT_H_ */
