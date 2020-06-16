##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CPPFLAGS	=	-iquote include

SRC		=	getSocket.c 			\
				manageEvent.c			\
				main.c						\
				tools.c						\
				command.c     		\
				server.c 					\
				str_breaker.c 		\

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
