#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>

#include "client_struct.h"

client_t *get_client_by_fd( client_t *head, int fd);

#endif /* CLIENT_H_ */
