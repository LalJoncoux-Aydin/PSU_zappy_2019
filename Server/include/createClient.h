#ifndef CREATECLIENT_H_
#define CREATECLIENT_H_

#include <stdbool.h>
#include <stdlib.h>

#include "server_struct.h"
#include "tools.h"
#include "command.h"

void createClient(client_t **head, int new_fd, server_t *server_v);

#endif /* CREATECLIENT_H_ */
