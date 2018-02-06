/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 12:29:11 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/06 12:29:12 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <inttypes.h>
#include "libftprintf.h"
#include "libft/libft.h"

// static uint8_t initial_shuffle[64] = {6, 14, 22, 30, 38, 46, 54, 62, 4, 12, 20,
// 28, 36, 44, 52, 60, 2, 10, 18, 26, 34, 42, 50, 58, 0, 8, 16, 24, 32, 40, 48,
// 56, 7, 15, 23, 31, 39, 47, 55, 63, 5, 13, 21, 29, 37, 45, 53, 61, 3, 11, 19,
// 27, 35, 43, 51, 59, 1, 9, 17, 25, 33, 41, 49, 57};

static uint8_t initial_shuffle[64] =
{57, 49, 41, 33, 25, 17, 9, 1,
 59, 51, 43, 35, 27, 19, 11, 3,
 61, 53, 45, 37, 29, 21, 13, 5,
 63, 55, 47, 39, 31, 23, 15, 7,
 56, 48, 40, 32, 24, 16, 8, 0,
 58, 50, 42, 34, 26, 18, 10, 2,
 60, 52, 44, 36, 28, 20, 12, 4,
 62, 54, 46, 38, 30, 22, 14, 6};

// static uint8_t pc1[56] = {3, 11, 19, 27, 4, 12, 20, 28, 36, 44, 52, 60, 5, 13,
// 21, 29, 37, 45, 53, 61, 6, 14, 23, 30, 38, 46, 54, 62, 35, 43, 51, 59, 2, 10,
// 18, 26, 34, 42, 50, 58, 1, 9, 17, 25, 33, 41, 49, 57, 0, 8, 16, 24, 32, 40,
// 48, 56};

static uint8_t pc1[56] =
{56, 48, 40, 32, 24, 16, 8,
 0, 57, 49, 41, 33, 25, 17,
 9, 1, 58, 50, 42, 34, 26,
 18, 10, 2, 59, 51, 43, 35,
 62, 54, 46, 38, 30, 22, 14,
 6, 61, 53, 45, 37, 29, 21,
 13, 5, 60, 52, 44, 36, 28,
 20, 13, 4, 27, 19, 11, 3};


int		ft_print_usage(void);
char	*ft_des_ecb(char *input);


int		main(int ac, char **av)
{
	char	*hh;

	if (ac == 3 && !ft_strcmp(av[1], "des"))
		hh = ft_des_ecb(av[2]);
	else
		return (ft_print_usage());
	ft_printf("result: %s\n", hh);
	ft_strdel(&hh);

	return (0);
}

uint64_t	ft_pc1_for_key(uint64_t key)
{
	uint64_t	ret;
	int			i;
	
	ret = 0;
	i = -1;
	while (++i < 56)
	{
		ret = ret | ((key >> (55 - pc1[i])) & 1);
		ret <<= 1;
	}
	return (ret);
}


char	*ft_des_ecb(char *input)
{
	uint64_t	conv;
	uint64_t	left_last;
	uint64_t	right_last;
	uint64_t	right_curr;
	uint64_t	left_curr;
	uint64_t	key;


	conv = 0;
	while (*input && (conv <<= 8) != -1)
		conv = conv | *input++;
	conv = 0x123456789ABCDEF; //for example
	ft_printf("binary before initial permutation:\n%.64b\n", conv);

	uint64_t	shuffled;
	int			i;

	uint64_t temp;

	shuffled = 0;
	i = -1;
	while (++i < 64)
	{
		shuffled <<= 1;
		shuffled = shuffled | ((conv >> (63 - initial_shuffle[i])) & 1);
	}
	ft_printf("binary  after initial permutation:\n%b\n", shuffled);

	left_last = shuffled >> 32;
	right_last = shuffled & 0xFFFFFFFF;
	ft_printf(" left = %b\nright = %.32b\n", left_last, right_last);

	key = 0x133457799BBCDFF1;
	ft_printf("key before PC-1:\n%.64b\n", key);
	key = ft_pc1_for_key(key);
	ft_printf("key  after PC-1:\n%.56b\n", key);
	printf("11110000110011001010101011110101010101100110011110001111\n");














	return (ft_strdup("res"));
}

int		ft_print_usage(void)
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (1);
}

