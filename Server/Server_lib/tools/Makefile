CPPFLAGS	=	-iquote ../../include

SRC		=	tool.c	\

OBJ		=	$(SRC:.c=.o)

NAME		=	libtools.a

CFLAGS		= -Wall -Wextra -g3

all: $(NAME)

$(NAME):	$(OBJ)
		ar rc $(NAME) $(OBJ)
		@echo -e "\e[92;5m       ==== Lib Command DONE ====      \e[0m"

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
