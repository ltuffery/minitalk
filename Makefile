# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 17:52:01 by ltuffery          #+#    #+#              #
#    Updated: 2022/12/17 18:19:36 by ltuffery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT		=	client

SERVER		=	server

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror

SERVER_SRCS	=	server.c

CLIENT_SRCS	=	client.c

SERVER_OBJS	=	$(SERVER_SRCS:.c=.o)

CLIENT_OBJS	=	$(CLIENT_SRCS:.c=.o)

%.o:			%.c
	$(CC) $(CFLAGS) -c $^ -o $@

all:			$(SERVER) $(CLIENT)

$(SERVER):		$(SERVER_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT):		$(CLIENT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(SERVER_OBJS) $(CLIENT_OBJS)

fclean:			clean
	rm -rf $(SERVER) $(CLIENT)

re:				fclean all

.PHONY:			all clean fclean re
