/*
** EPITECH PROJECT, 2019
** server
** File description:
** manage_event.h
*/

#ifndef MANAGE_EVENT_H_
#define MANAGE_EVENT_H_

#include "create_client.h"
#include "manage_client.h"

void manage_event(fd_set *master, server_t *server_v, int *fd_max, fd_set *read, client_t *head);

#endif /* MANAGE_EVENT_H_ */
