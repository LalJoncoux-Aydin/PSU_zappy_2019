#include "manageEvent.h"

static void addClient(client_t **head, server_t *serv, fd_set *master)
{
    struct sockaddr_storage cli;
    socklen_t sockl = sizeof(struct sockaddr_storage);
    int new;

    if ((new = accept(serv->server_fd, (struct sockaddr *)&cli, &sockl)) == -1)
        error("accept failed that's unnacceptable");
    FD_SET(new, master);
    serv->server_fd = new > serv->server_fd ? new : serv->server_fd;
    createClient(head, new, serv);
}

void manageEvent(fd_set *master, server_t *server_v, fd_set *read_fds)
{
    static client_t *head = NULL;

    for (int i = 0; i <= server_v->server_fd; i++) {
        if (FD_ISSET(i, read_fds)) {
            i == server_v->server_fd ? addClient(&head, server_v, master) : manageClient(&head, server_v, i, master);
        }
    }
}
