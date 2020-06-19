#include "command.h"

void pnw(client_t *cli)
{
    char *buff = malloc(50);

    memset(buff, 0, 50);
    sprintf(buff, "pnw %d %d %d %d %d %s\n", cli->ai->player_number,
    cli->ai->x, cli->ai->y, cli->ai->orientation, cli->ai->level, cli->ai->team);
    if (DEBUG)
        printf("%s",buff);
    //struct timespec tim, tim2;
    //tim.tv_sec = 1;
    //tim.tv_nsec = 500;
    //nanosleep(&tim , &tim2);
    for (; cli->prev ; cli = cli->prev);
    for (; cli ; cli = cli->next)
        send(cli->fd, buff, strlen(buff), 0);
}
