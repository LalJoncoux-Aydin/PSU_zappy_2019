/*
** EPITECH PROJECT, 2019
** server command
** File description:
** msz.c
*/

#include "command.h"

void nbp(int fd_cli, client_t *clis, server_t *server,
__attribute__((unused))char *command)
{
	char *nb_player = NULL;
	int nb = 0;

	nb_player = malloc(sizeof(char) * MESSAGE_SIZE);
	if (nb_player == NULL)
		error("Error : Malloc failed\n");
	for (client_t *temp = clis; temp; temp = temp->next, nb++);
	sprintf(nb_player, "nbp %d\n", nb);
	send(fd_cli, nb_player, strlen(nb_player), 0);
	free(nb_player);
}
