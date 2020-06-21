/*
** EPITECH PROJECT, 2019
** server
** File description:
** server.h
*/

#ifndef SERVER_H_
#define SERVER_H_

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define TEAMS_NB 200
#define HELP "USAGE: ./zappy_server -p port -x width -y height -n name1 name2\
... -c clientsNb -f freq\n\t\
port is the port number\n\t\
width is the width of the world\n\t\
height is the height of the world\n\t\
nameX is the name of the team X\n\t\
clientsNb is the number of authorized clients per team\n\t\
freq is the reciprocal of time unit for execution of actions\n"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
#include <signal.h>

#include "tools.h"
#include "get_socket.h"
#include "manage_arg.h"
#include "add_client.h"
#include "map.h"
#include "server_struct.h"

server_t *init_server(server_t *server_v);
int server(server_t *server_v);

#endif /* SERVER_H_ */
