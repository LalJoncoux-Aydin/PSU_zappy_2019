#ifndef TOOLS_H_
#define TOOLS_H_

#include "server_struct.h"

char *str_breaker(char *line, char delim, int part, int strict);
void add_end_file(char *str, char *str_name);
void error(char *msg);
int occurrences_of_char(char c, char *str);
void send_all(int fd, char *msg);
int *tri_force(int a, int b, int c);
int str_in_str(char *needle, char *haystackt);
int return_type(char *str);
void error_s(int fd);
int get_rand_num(int min, int max, int percent);

#endif /* TOOLS_H_ */
