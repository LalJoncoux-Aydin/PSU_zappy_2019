CPPFLAGS	=	-iquote ../../include

SRC		=	bct.c			\
			forward.c		\
			look.c			\
			mct.c			\
			msz.c			\
			pnw.c			\
			ppo_plv_pin.c	\
			tna.c			\
			turn.c			\
			take.c			\
			nbp.c			\
			fork_cli.c			\
			elevation.c		\

OBJ		=	$(SRC:.c=.o)

NAME		=	libcommand.a

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
