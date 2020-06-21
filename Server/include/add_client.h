/*
** EPITECH PROJECT, 2019
** server
** File description:
** manage_event.h
*/

#ifndef ADD_CLIENT_H_
#define ADD_CLIENT_H_

#include "create_client.h"
#include "manage_client.h"

client_t *add_first_client(server_t *serv);
void add_client(server_t *serv, client_t *head);

#endif /* ADD_CLIENT_H_ */
