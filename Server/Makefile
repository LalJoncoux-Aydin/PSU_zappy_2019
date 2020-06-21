##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CPPFLAGS	=	-iquote include

SRC		=	manage_arg.c						\
			get_team_name.c						\
			add_client.c						\
			create_client.c						\
			manage_client.c						\
			map.c								\
			get_socket.c 						\
			server.c 							\
			main.c								\

SRC_FILE	=	$(addprefix ./src/, $(SRC))

OBJ		=	$(SRC_FILE:.c=.o)

NAME		=	zappy_server

LDFLAGS =  -L./Server_lib/commands/ -lcommand -L./Server_lib/tools/ -ltools -luuid

CFLAGS		= -Wall -Wextra -g3

all: $(NAME)

commands:
	make -C ./Server_lib/commands/

tools:
	make -C ./Server_lib/tools/

$(NAME):	tools	commands	$(OBJ)
		gcc -o $(NAME) $(OBJ) $(LDFLAGS)
		@echo -e "\e[92;5m       ====BULDING DONE====      \e[0m"
		cp $(NAME) ../.

clean:
	rm -f $(OBJ)
	make clean -C ./Server_lib/commands/
	make clean -C ./Server_lib/tools/

fclean:
	rm -f $(OBJ)
	rm -f $(NAME)
	make fclean -C ./Server_lib/commands/
	make fclean -C ./Server_lib/tools/

re:	fclean all

.PHONY: all clean fclean re commands tools
