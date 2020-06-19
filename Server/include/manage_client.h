/*
** EPITECH PROJECT, 2019
** server
** File description:
** manage_client.h
*/

#ifndef MANAGE_CLIENTT_H_
#define MANAGE_CLIENT_H_

#include "command.h"

void manage_client(fd_set *master, server_t *server_v, int i, client_t **head);

#endif /* MANAGE_CLIENT_H_ */
