# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taehkim <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 16:08:44 by taehkim           #+#    #+#              #
#    Updated: 2020/12/04 16:23:14 by taehkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
HDR		=	-include ./inc/minishell.h
LIBFT	=	libft/libft.a
SRCS	=	./srcs/chdir.c \
			./srcs/echo.c \
			./srcs/env.c \
			./srcs/exit.c \
			./srcs/export.c \
			./srcs/get_next_line.c \
			./srcs/get_next_line_utils.c \
			./srcs/init.c \
			./srcs/main.c \
			./srcs/parse.c \
			./srcs/pipe.c \
			./srcs/pwd.c \
			./srcs/redirect.c \
			./srcs/unset.c \
			./srcs/update.c \
			./srcs/utils.c \

OBJS	=	$(SRCS:%.c=%.o)

all		:	$(NAME)

$(LIBFT):
	$(MAKE) -C libft

%.o		:	%.c
	$(CC) $(CFLAGS) $(HDR) -o $@ -c $<

$(NAME)	:	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(HDR) -o $@ $(LIBFT) $(OBJS)

clean	:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean	:	clean
	rm -f $(NAME) 
	$(MAKE) -C libft fclean

re		:	fclean	all

.PHONY	:	all clean fclean re
