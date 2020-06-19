/*
** EPITECH PROJECT, 2019
** server tools
** File description:
** tool.c
*/

#include "tools.h"

void add_end_file(char *str, char *str_name)
{
    FILE *_file = NULL;

    _file = fopen(str_name, "a");
    if (_file == NULL)
        exit(84);
    fputs(str, _file);
    fputs("\n", _file);
    fclose(_file);
}

void error(char *msg)
{
    printf("%s", msg);
    exit(84);
}

int occurrences_of_char(char c, char *str)
{
    int res = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            res++;
    return res;
}

void send_all(int fd, char *msg)
{
    int ret;
    int bytes = 0;
    int buflen = strlen(msg);
    char *buff = msg;
    int retry = 0;

    while (bytes < buflen) {
        retry = 0;
        ret = send(fd, buff + bytes, buflen - bytes, 0);
        if (ret == -1) {
            retry != 5 ? retry += 1 : error("send fail");
            continue;
        }
        bytes += ret;
    }
}

int *tri_force(int a, int b, int c)
{
    int *res = malloc(sizeof(int) * 3);

    if (res == NULL)
        error("Malloc fail");
    res[0] = a;
    res[1] = b;
    res[2] = c;
    return res;
}

void error_s(int fd)
{
    char *msg = strdup("ko\n");

    if (msg == NULL)
        error("Strdup fail");
    send(fd , msg, strlen(msg), 0);
    free(msg);
}

int get_rand_num(int min, int max, int percent)
{
    int res;
    int act = (rand() % 100);

    if (percent < act)
        return 0;
    if (min > max)
        return min;
    res = rand() % max;
    while (res < min)
        res = rand() % max;
    return res;
}

char *str_concat(char *con, char *cat)
{
    if (!con || !cat)
        return NULL;
    con = realloc(con, strlen(con) + strlen(cat) + 1);
    if (!con)
        return NULL;
    return strcat(con, cat);
}

char *str_breaker(char *line, char delim, int part, int strict)
{
    int pos = 1;
    char *res = malloc(sizeof(char) * strlen(line));
    int j;

    for (int i = 0; line[i]; i++) {
        if (pos == part) {
            for (j = 0; line[i] && line[i] != delim; i++)
                res[j++] = line[i];
            res[j] = '\0';
            if (!line[i] && strict == 1){
                free(res);
                return NULL;
            }
            return res;
        }
        if (line[i] == delim)
            pos++;
    }
    free(res);
    return NULL;
}

int eq_str(char *str1, char *str2)
{
    for (int i = 0; str1[i] && str2[i]; i++)
        if (str1[i] != str2[i])
            return 0;
    return 1;
}

int str_in_str(char *needle, char *haystackt)
{
    for (int i = 0; haystackt[i]; i++) {
        for (int y = 0; needle[y] == haystackt[i]; y++) {
            if (needle[y + 1] == '\0')
                return 1;
            if (haystackt[i++] == '\0')
                return 0;
        }
    }
    return 0;
}

int return_type(char *str)
{
    int status = 0;

    if (DEBUG) {
        if (!(strlen(str) < 7) && str[5] == 'a' && str[6] == 'i')
            status = 1;
        else
            status = 2;
        printf("CLI of type %s connected\n", status == 1 ? "AI" : "GRAPHIC");
    }
    if (strlen(str) < 7)
        return -1;
    if (!(strlen(str) < 7) && str[5] == 'a' && str[6] == 'i')
        return AI;
    return GRAPHIC;
}

void add_new_fd(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    if (*fd_count == *fd_size) {
        *fd_size *= 2;
        *pfds = realloc(*pfds, sizeof(struct pollfd **) * (*fd_size));
        if (*pfds == NULL)
            error("Realloc fail");
    }
    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN;
    (*fd_count)++;
}

client_t *get_client_by_fd(client_t *head, int fd)
{
    if (head)
        for (; head != NULL; head = head->next) {
            if (head->fd == fd)
                return head;
        }
    return NULL;
}
