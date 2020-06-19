#include "command.h"

void msz(int fd_cli, client_t *clis __attribute__((unused)), server_t *server ,char *command __attribute__((unused)))
{
    char *buff = malloc(20);

    memset(buff, 0, 20);
    sprintf(buff, "msz %d %d\n", server->x, server->y);
    send(fd_cli, buff, strlen(buff), 0);
    if (DEBUG)
        printf("message send : %s",buff);
    free(buff);
}
