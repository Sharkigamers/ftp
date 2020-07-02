##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SERVER_DIR		=		server_ftp/

################################################################################

all: server

debug:
	@ make debug -C $(SERVER_DIR) -s

server:
	@ make -C $(SERVER_DIR) -s

clean:
	@ make clean -C $(SERVER_DIR) -s

fclean:
	@ make fclean -C $(SERVER_DIR) -s

re:
	@ make re -C $(SERVER_DIR) -s

de:
	@ make de -C $(SERVER_DIR) -s

.PHONY: all server clean fclean re de