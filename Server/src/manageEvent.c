#include "manageEvent.h"

static void add_cli_spe(client_t *cli, server_t *server_v, char *team)
{
    int i = 0;

    if (cli->type == GRAPHIC)
        return;
    cli->ai = malloc(sizeof(client_t));
    cli->ai->x = get_rand_num(0, server_v->x, 100);
    cli->ai->y = get_rand_num(0, server_v->y, 100);
    if (cli->ai->y > server_v->y / 2)
        cli->ai->orientation = NORTH;
    else
        cli->ai->orientation = SOUTH;
    cli->ai->player_number = nbr_player++;
    for (i = 0; server_v->teams_name[i] ; i++) {
        if (str_in_str(server_v->teams_name[i],team)){
            printf("<->%s<->%s<->\n",server_v->teams_name[i], team);
            printf("VICTOIRE\n");
            cli->ai->team = strdup(team);
            break;
        }
    }
    cli->ai->level = 0;
    if (!server_v->teams_name[i]) {
        printf("%s\n",team);
        printf("ai teams  : %s\n->not found error\n", team);
        error_s(cli->fd);
    }
    pnw(cli);
}

static void add_cli(client_t **head, int new_fd, server_t *server_v)
{
    client_t *buff = NULL;
    client_t *buff_prev = NULL;
    char *type = NULL;
    char *team = NULL;
    int size = 0;

    buff = *head;
    type = malloc(sizeof(char) * 50);
    if (type == NULL)
      error("Malloc failed");
    team = malloc(sizeof(char) * 50);
    if (team == NULL)
      error("Malloc failed");
    printf("Start memset\n");
    memset(type, 0 , 50);
    recv(new_fd, type, 50, 0);
    memset(team, 0 , 50);
    recv(new_fd, team, 50, 0);
    printf("caca\n");
    team[10 -1] = '\0';
    printf("caca\n");
    if (!(*head)) {
        (*head) = malloc(sizeof(client_t));
        (*head)->fd = new_fd;
        (*head)->prev = NULL;
        (*head)->next = NULL;
        (*head)->type = return_type(type);
        free(type);
        return add_cli_spe((*head),server_v, team);
    }
    for (; buff->next != NULL ; buff = buff->next );
    buff->next = malloc(sizeof(client_t));
    buff_prev = buff;
    buff = buff->next;
    buff->fd = new_fd;
    buff->type  = return_type(type);
    buff->next = NULL;
    buff->prev = buff_prev;
    free(type);
    printf("end add cli");
    return  add_cli_spe(buff,server_v, team);
}

static void del_cli(client_t **head, int fd)
{
    client_t *temp = *head;
    client_t *prev;

    if (temp != NULL && temp->fd == fd) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->fd != fd) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}

static void manage_message(char *msg, int *tri_force, client_t *clis, server_t *server)
{
    int sender_fd = tri_force[1];

    for (int i = 0; i < NBR_OF_COMMAND; i++) {
        if (str_in_str(commands[i].command, msg))
            commands[i].func(sender_fd, clis, server, msg);
    }
}

void manage_event(fd_set *master,server_t *server_v, int i, int *fd_max)
{
    struct sockaddr_storage cli_addr;
    socklen_t addrlen = sizeof(struct sockaddr_storage);
    int nbytes;
    static client_t *head = NULL;
    char buff[256 * 4];
    int new_fd;

    if (i == server_v->server_fd) {
        printf("New cli\n");
        if ((new_fd = accept( server_v->server_fd, (struct sockaddr *)&cli_addr, &addrlen)) == -1)
            error("accept failed that's unnacceptable");
        printf("??\n");
        FD_SET(new_fd, master);
        printf("??\n");
        *fd_max = new_fd > *fd_max ? new_fd : *fd_max;
        printf("??\n");
        add_cli(&head, new_fd, server_v);
        printf("CLIENT ADDED\n");
    } else {
        printf("Old cli\n");
        if ((nbytes = recv(i, buff, sizeof(buff), 0)) <= 0) {
            del_cli(&head, i);
            close(i);
            FD_CLR(i, master);
        }
        buff[nbytes] = '\0';
        manage_message(buff,
        tri_force(*fd_max, i, 0), head, server_v);
    }
}
