##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CPPFLAGS	=	-iquote include

SRC		=	tool.c 								\
			command.c     						\
			command2.c							\
			manageArg.c							\
			manageEvent.c						\
			createClient.c						\
			manageClient.c						\
			map.c								\
			getSocket.c 						\
			server.c 							\
			main.c								\

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
