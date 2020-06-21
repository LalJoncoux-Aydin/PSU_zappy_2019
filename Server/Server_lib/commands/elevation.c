/*
** EPITECH PROJECT, 2019
** server command
** File description:
** bct.c
*/

#include "command.h"

//  FD CLI -> fd du client qui te parle
//  CLIENT -> client qui te parle (définit dans include/struct_server.h)
//  SERVER -> server (definit dans include/struct_server.h)
//  COMMAND -> ton message (regarde dans /tools il y a des outils pour le manipuler)
void elevation(int fd_cli, client_t *clis, server_t *server, char *command)
{
    char *buff = NULL;

    buff = malloc(sizeof(char) * MESSAGE_SIZE);
    if (buff == NULL)
        error("Error : malloc failed\n");
	// TODO : Remplir le buffer
    send(fd_cli, buff, strlen(buff), 0);
    free(buff);
}
