# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 17:52:01 by ltuffery          #+#    #+#              #
#    Updated: 2022/12/21 15:46:44 by ltuffery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT		=	client

SERVER		=	server

LIBFT_DIR	=	libft

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror -Ofast

SERVER_SRCS	=	server.c

CLIENT_SRCS	=	client.c

SERVER_OBJS	=	$(SERVER_SRCS:.c=.o)

CLIENT_OBJS	=	$(CLIENT_SRCS:.c=.o)

%.o:			%.c
	$(CC) $(CFLAGS) -c $^ -o $@

all:			$(SERVER) $(CLIENT)

$(SERVER):		$(SERVER_OBJS)
	@make -s -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $^ $(LIBFT_DIR)/libft.a -o $@

$(CLIENT):		 $(CLIENT_OBJS)
	@make -s -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $^ $(LIBFT_DIR)/libft.a -o $@

clean:
	rm -rf $(SERVER_OBJS) $(CLIENT_OBJS)
	@make clean -s -C $(LIBFT_DIR)

fclean:			clean
	rm -rf $(SERVER) $(CLIENT)
	@make fclean -s -C $(LIBFT_DIR)

re:				fclean all

test:
	@make -s -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) tests/client.c libft/libft.a -o tests/client
	$(CC) $(CFLAGS) tests/server.c libft/libft.a -o tests/server
	@make fclean -s -C $(LIBFT_DIR)

.PHONY:			all clean fclean re
