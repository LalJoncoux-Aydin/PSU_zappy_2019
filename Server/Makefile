##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CPPFLAGS	=	-iquote include

SRC		=	add_cli.c 				\
			get_socket_server.c 	\
			main.c 					\
			server.c 				\
			command/command2.c 		\
			command/command.c 		\
			command/look.c 			\
			command/take.c 			\
			tool/str_breaker.c  	\
			tool/tool2.c 			\
			tool/tool3.c 			\
			tool/tool.c


SRC_FILE	=	$(addprefix ./src/, $(SRC))

OBJ		=	$(SRC_FILE:.c=.o)

NAME		=	zappy_server

LDFLAGS = -luuid

CFLAGS		= -Wall -Wextra -g3

all: $(NAME)

clean:
	rm -f $(OBJ)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(LDFLAGS) $(OBJ)
		@echo -e "\e[92;5m       ====BULDING DONE====      \e[0m"

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
