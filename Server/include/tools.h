/*
** EPITECH PROJECT, 2019
** server
** File description:
** tools.h
*/

#ifndef TOOLS_H_
#define TOOLS_H_

#define DEBUG 1

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "server_struct.h"

char *str_breaker(char *line, char delim, int part, int strict);
void error(char *msg);
int str_in_str(char *needle, char *haystackt);
int get_rand_num(int min, int max, int percent);
char *str_concat(char *con, char *cat);

#endif /* TOOLS_H_ */
