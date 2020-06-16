/*
** EPITECH PROJECT, 2019
** point h
** File description:
** HEADER
*/

#ifndef SERVER_H_
#define SERVER_H_

#define TEAMS_NB 6
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define HELP "USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\n\t\
port is the port number\n\t\
width is the width of the world\n\t\
height is the height of the world\n\t\
nameX is the name of the team X\n\t\
clientsNb is the number of authorized clients per team\n\t\
freq is the reciprocal of time unit for execution of actions\n"

//Standard include
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <uuid/uuid.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <poll.h>
#include <ctype.h>
#include <getopt.h>

//Private include
#include "tools.h"
#include "client.h"
#include "manageEvent.h"
#include "command.h"
#include "server_struct.h"

server_t *initServer(server_t *server_v);
int server(server_t *port);

#endif /* SERVER_H_ */
