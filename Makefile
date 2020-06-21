##
## EPITECH PROJECT, 2020
## PSU_zappy_2019
## File description:
## Makefile
##
# Mandatory
SHELL				= /bin/sh

IA_FOLDER 			= Client
GRAPHICAL_FOLDER 	= Build
SERVER_FOLDER 		= Server

NAME_FILE_IA		= zappy_ai.py
NAME_IA				= zappy_ai
NAME_GRAPHIC 		= Zappy.exe
NAME_SERVER			= zappy_server

all: unzip server ia

unzip:
	unzip Build.zip
	cp $(GRAPHICAL_FOLDER)/${NAME_GRAPHIC} .

server:
	make -C ${SERVER_FOLDER}/
	mv ${SERVER_FOLDER}/${NAME_SERVER} .

ia:
	cp ${IA_FOLDER}/${NAME_FILE_IA} .
	mv $(NAME_FILE_IA) $(NAME_IA)
	chmod 777 $(NAME_IA)

clean:
	make clean -C  ${SERVER_FOLDER}/
	rm -fr ${IA_FOLDER}/src/__pycache__/
	rm -fr ${IA_FOLDER}/__pycache__/

fclean: clean
	rm -fr $(NAME_SERVER)
	rm -fr $(NAME_IA)
	rm -fr $(NAME_GRAPHIC)
	rm -fr $(GRAPHICAL_FOLDER)

re: fclean all

.PHONY: fclean all re clean ia server
