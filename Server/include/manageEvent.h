#ifndef MANAGEEVENT_H_
#define MANAGEEVENT_H_

#include "createClient.h"
#include "manageClient.h"

void manageEvent(fd_set *master, server_t *server_v, fd_set *read_fds);

#endif /* MANAGEEVENT_H_ */
