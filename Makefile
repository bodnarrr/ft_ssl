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
		ft_base64_encoding.c ft_base64_decoding.c ft_desecb.c \
		ft_desecb_encoding.c ft_desfuncs.c ft_descheckkeys.c \
		ft_desecb_decoding.c ft_ssl_get_str.c ft_ssl_write.c \
		ft_ssl_join_block.c ft_des_join_block.c ft_descbc.c \
		ft_descbc_encoding.c ft_des_make_keyvector.c \
		ft_descbc_decoding.c

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

re: clean all

.PHONY: all clean fclean re
