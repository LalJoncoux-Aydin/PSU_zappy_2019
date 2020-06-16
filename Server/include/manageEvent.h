/*
** EPITECH PROJECT, 2019
** point h
** File description:
** HEADER
*/

#ifndef MANAGEEVENT_H_
#define MANAGEVENT_H_

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

#include "tools.h"
#include "client_struct.h"
#include "server_struct.h"
#include "command.h"

static int nbr_player = 0;

void manage_event(fd_set *master,server_t *server_v, int i, int *fd_max);

#endif /* SERVER_H_ */
