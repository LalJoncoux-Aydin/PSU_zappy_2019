#ifndef MANAGECLIENTT_H_
#define MANAGECLIENT_H_

#include "command.h"

void manageClient(client_t **head, server_t *server_v, int i, fd_set *master);

#endif /* MANAGECLIENT_H_ */
