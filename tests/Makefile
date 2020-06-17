##
## EPITECH PROJECT, 2017
## make
## File description:
## make
##

CC	=	gcc

NAME	=	calc

SRC	=	../Server/src/tool.c				\
		../Server/src/server.c				\
		../Server/src/tool2.c				\
		../Server/src/command.c				\
		../Server/src/command2.c			\
		../Server/src/str_breaker.c			\
		../Server/src/get_socket_server.c	\
		../Server/src/poll_tool.c			\

OBJ	=	$(SRC:.c=.o)

CFLAGS	+=	-I../Server/include -Werror -Wextra -Wall -ofast

all: 		$(NAME)

$(NAME): 	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)
		cp $(NAME) ./script_test/

tests_run:
	$(CC) $(SRC) Tests/*.c --coverage -lcriterion -I../Server/include
	./a.out
	rm *.gcno
	rm *.gcda

clean:
		rm -f $(OBJ)

coverage_clean:
		rm -f *.gc*
		rm -f src/*.gc*

fclean: 	clean coverage_clean
		rm -f $(NAME)
		rm -f ./script_test/$(NAME)

re:		fclean all

.PHONY:		all clean fclean re