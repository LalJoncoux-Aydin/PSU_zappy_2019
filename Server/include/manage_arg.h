/*
** EPITECH PROJECT, 2019
** server
** File description:
** manage_arg.h
*/

#ifndef MANAGE_ARG_H_
#define MANAGE_ARG_H_

#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "tools.h"
#include "server_struct.h"

bool manage_arg(int ac, char **av, server_t *server_v, char **env);

#endif /* MANAGE_ARG_H_ */
