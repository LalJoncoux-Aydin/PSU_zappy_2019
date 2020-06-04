#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int ac, char **av)
{
    char *buf = NULL;

    if (ac != 2)
        return 84;
    if (!strcmp(av[1], "-h")  || !strcmp(av[1], "-help")) {
        printf("%s", HELP);
        return 0;
    }
    buf = strdup(av[1]);
    for (int j = 0; buf[j]; ++j) {
        if (!isdigit(buf[j]))
            return 84;
    }
    server("8000");
    return 0;
}
