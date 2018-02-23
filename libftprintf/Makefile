# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abodnar <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/12 12:19:01 by abodnar           #+#    #+#              #
#    Updated: 2018/01/12 16:26:37 by abodnar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c ft_parse_printf.c ft_get_numbers.c ft_get_unsign_ptr_bin.c \
	ft_prec_width.c ft_flags.c ft_get_unichar.c ft_get_unistr.c \
	ft_sharp_octal_hexa.c ft_zero_nonptr.c ft_apply_flags.c \
	ft_typical_or_unicode_arg.c ft_prec_for_nonstring.c

OFLS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o : %.c
	@gcc -I. -Wall -Werror -Wextra -c $< -o $@

$(NAME): $(OFLS) libftprintf.h
	@make -C libft
	@cp ./libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OFLS)
	@ranlib $(NAME)
	@echo "\033[1;32mLIBFTPRINTF is ready"

clean:
	@make clean -C libft/
	@/bin/rm -f $(OFLS)
	@echo "\033[0;32mObject files ft_printf were removed"

fclean: clean
	@make fclean -C libft/
	@/bin/rm -f libft.a
	@/bin/rm -f $(NAME)
	@echo "\033[0;32mlibftprintf.a was removed\033[0m"

re: fclean all
