##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## Makefile
##

NAME_IA	= 	zappy_ai
NAME_SERVER	=	zappy_server

all: server ia

server:
	make -C Server/
	mv Server/zappy_server .

ia:
	cp ./Client/zappy_ai.py $(NAME_IA) && chmod +x $(NAME_IA)

clean:
	make clean -C  Server/
	rm -rf Client/src/__pycache__/
	rm -rf Client/__pycache__/

fclean: clean
	rm -rf $(NAME_SERVER)
	rm -rf $(NAME_IA)


re: fclean all

.PHONY: fclean all re clean ia server
