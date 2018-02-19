# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abodnar <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/16 12:17:53 by abodnar           #+#    #+#              #
#    Updated: 2018/02/16 12:17:53 by abodnar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
LIB = libftprintf.a

SRCS = main.c ft_ssl_errors.c ft_base64.c ft_ssl_get_commands.c \
		ft_base64_encoding.c ft_base64_decoding.c

OBJECTS = $(SRCS:.c=.o)

CC = gcc
FLAGS ?= -Wall -Wextra -Werror
FLAGS += -I./src/ -I./libft/

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB)
	@$(CC) -o $@ $(FLAGS) $(OBJECTS) $(LIB)

$(LIB):
	@make -C ./libftprintf/

clean:
	@make -C ./libftprintf/ fclean
	@rm $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
