/*
** EPITECH PROJECT, 2019
** server
** File description:
** command.h
*/

#ifndef GETSOCKET_H_
#define GETSOCKET_H_

#include "tools.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int getSocket(char *port);

#endif
