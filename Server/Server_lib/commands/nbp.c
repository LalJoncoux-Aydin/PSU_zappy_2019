/*
** EPITECH PROJECT, 2019
** server command
** File description:
** msz.c
*/

#include "command.h"

void nbp(int fd_cli, __attribute__((unused))client_t *cli, server_t *server,
__attribute__((unused))char *command)
{
	char *nb_player = NULL;

	nb_player = malloc(sizeof(char) * MESSAGE_SIZE);
	if (nb_player == NULL)
		error("Error : Malloc failed\n");
	sprintf(nb_player, "nbp %d\n", server->nb_player);
	send(fd_cli, nb_player, strlen(nb_player), 0);
	free(nb_player);
}
