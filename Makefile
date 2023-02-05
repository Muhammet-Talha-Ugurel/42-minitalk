#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mugurel <muhammedtalhaugurel@gmai...>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 23:34:08 by mugurel           #+#    #+#              #
#    Updated: 2023/02/02 23:34:10 by mugurel          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = program
SERVER = server
CLIENT = client
CC = gcc
LIB = ./minitalk_lib.c
CFLAGS = -Wall -Werror -Wextra

all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER):
	$(CC) $(CFLAGS) server.c $(LIB) -o $(SERVER)

$(CLIENT):
	$(CC) $(CFLAGS) client.c $(LIB) -o $(CLIENT)

clean:
	make fclean -C ./ft_printf

fclean: clean
	rm -rf $(SERVER)
	rm -rf $(CLIENT)

re: fclean all

.PHONY: all flean clean re
