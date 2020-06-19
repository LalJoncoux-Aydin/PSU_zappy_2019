#ifndef MANAGEARG_H_
#define MANAGEARG_H_

#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "tools.h"
#include "server_struct.h"

void manageArg(int ac, char **av, server_t *server_v, char **env);

#endif /* MANAGEARG_H_ */
