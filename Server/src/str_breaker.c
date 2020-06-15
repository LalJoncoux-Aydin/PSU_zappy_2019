/*
** EPITECH PROJECT, 2019
** PSU_tetris_2018
** File description:
** str_breaker.c
*/

#include <stdlib.h>
#include <string.h>
#include "tools.h"


char *str_breaker(char *line, char delim, int part, int strict)
{
    int pos = 1;
    char *res = malloc(sizeof(char) * strlen(line));
    int j;

    //part = part == 0 ? 1 : part;
    for (int i = 0; line[i] ; i++) {
        if (pos == part){
            for(j = 0; line[i] && line[i] != delim; i++)
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

//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <unistd.h>

//int main(int ac, char **av)
//{
//    //main dexemple
//    char *buff = strdup("IL etait une fois\n");
//    char *buff2 = strdup("LOLLOL");
//    char *buff3 = malloc(1000);
//    int file_fd = open("../recods/users/jonathan", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR );
//    read(file_fd, buff3, 1000);
//    printf("%s\n", str_breaker(buff2, ' ', 1, 0));
//    printf("%d\n", (str_breaker(buff2, ' ', 1, 0) == 0));
//    printf("%d\n", (str_breaker(buff2, ' ', 1, 1) == 0));
//    printf("%s\n", str_breaker(buff, ' ', 1, 0));
//    printf("%s\n", str_breaker(buff, ' ', 2, 0));
//    printf("%s\n", str_breaker(buff, ' ', 3, 0));
//    printf("%s\n", str_breaker(buff, ' ', 4, 0));
//    printf("%d\n", (str_breaker(buff, ' ', 5, 0) == 0));
//    printf("****\n%s\n******",buff3);
//    printf("->>%s\n", str_breaker(buff3, '\n', 1 , 0));
//    for (int i = 1; str_breaker(buff3, '\n', i , 0) != NULL ; i++)
//            printf("%d ->> %s \n",i ,str_breaker(buff3, '\n', i , 0));
//}