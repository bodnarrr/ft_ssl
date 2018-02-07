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

#define C4BITS(x) x >> 1 & 0xF
#define E2BITS(x) (x & 1) | (x >> 4 & 2)


static uint8_t initial_shuffle[64] =
	{57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7,
	56, 48, 40, 32, 24, 16, 8, 0,
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6};

static uint8_t pc1[56] =
	{56, 48, 40, 32, 24, 16, 8,
	0, 57, 49, 41, 33, 25, 17,
	9, 1, 58, 50, 42, 34, 26,
	18, 10, 2, 59, 51, 43, 35,
	62, 54, 46, 38, 30, 22, 14,
	6, 61, 53, 45, 37, 29, 21,
	13, 5, 60, 52, 44, 36, 28,
	20, 12, 4, 27, 19, 11, 3};

 static uint8_t pc2[48] = 
	{13, 16, 10, 23, 0, 4,
	2, 27, 14, 5, 20, 9,
	22, 18, 11, 3, 25, 7,
	15, 6, 26, 19, 12, 1,
	40, 51, 30, 36, 46, 54,
	29, 39, 50, 44, 32, 47,
	43, 48, 38, 55, 33, 52,
	45, 41, 49, 35, 28, 31};

static uint8_t key_shift[16] =
	{1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

static uint8_t expand_right[48] = 
	{31, 0, 1, 2, 3, 4,
	3, 4, 5, 6, 7, 8,
	7, 8, 9, 10, 11, 12,
	11, 12, 13, 14, 15, 16,
	15, 16, 17, 18, 19, 20,
	19, 20, 21, 22, 23, 24,
	23, 24, 25, 26, 27, 28,
	27, 28, 29, 30, 21, 0};

static uint8_t six_to_four1[64] =
	{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
	0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
	4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
	15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};

static uint8_t six_to_four2[64] =
	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
	3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
	0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
	13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};

static uint8_t six_to_four3[64] =
	{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
	13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
	13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
	1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12};

static uint8_t six_to_four4[64] =
	{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
	13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
	10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
	3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};

static uint8_t six_to_four5[64] =
	{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
	14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
	4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
	3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};

static uint8_t six_to_four6[64] =
	{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
	10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
	9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
	4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};

static uint8_t six_to_four7[64] = 
	{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
	13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
	1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
	6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};

static uint8_t six_to_four8[64] =
	{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
	1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
	7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
	2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

static uint8_t *(six_to_four[]) =
	{six_to_four1,	six_to_four2, six_to_four3, six_to_four4,
	six_to_four5, six_to_four6, six_to_four7, six_to_four8};


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

uint64_t	ft_expand_right(uint64_t inf)
{
	uint64_t	ret;
	int			i;
	
	ret = 0;
	i = -1;
	while (++i < 48)
	{
		ret <<= 1;
		ret = ret | ((inf >> (31 - expand_right[i])) & 1);
	}
	return (ret);
}

uint64_t	ft_pc1_for_key(uint64_t key)
{
	uint64_t	ret;
	int			i;
	
	ret = 0;
	i = -1;
	while (++i < 56)
	{
		ret <<= 1;
		ret = ret | ((key >> (63 - pc1[i])) & 1);
	}
	return (ret);
}

uint64_t	ft_pc2_for_key(uint64_t key)
{
	uint64_t	ret;
	int			i;
	
	ret = 0;
	i = -1;
	while (++i < 48)
	{
		ret <<= 1;
		ret = ret | ((key >> (55 - pc2[i])) & 1);
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
	uint64_t	key_left;
	uint64_t	key_right;
	uint64_t	key_curr;
	uint64_t	temp;
	uint64_t	temp6bit;


	conv = 0;
	while (*input && (conv <<= 8) != -1)
		conv = conv | *input++;

	uint64_t	shuffled;
	int			i;

	shuffled = 0;
	i = -1;
	while (++i < 64)
	{
		shuffled <<= 1;
		shuffled = shuffled | ((conv >> (63 - initial_shuffle[i])) & 1);
	}

	left_last = shuffled >> 32;
	right_last = shuffled & 0xFFFFFFFF;

	key = ft_pc1_for_key(key);

	key_left = key >> 28;
	key_right = key & 0xFFFFFFF;
	key_curr = ((key_left << 1 & 0xEFFFFFFF) | ((key_left >> 27) & 1)) << 28 | ((key_right << 1 & 0xEFFFFFFF) | ((key_right >> 27) & 1));
	key_curr = 0xE19955FAACCF1E;
	key_curr = ft_pc2_for_key(key_curr);
	right_last = 0xF0AAF0AA;
	right_curr = ft_expand_right(right_last);
	right_curr = right_curr ^ key_curr;
	i = -1;
	temp = 0;
	while (++i < 8)
	{
		temp <<= 4;
		temp6bit = right_curr >> (42 - i * 6) & 0x3F;
		ft_printf("6bit: %.6b\n", temp6bit);
		ft_printf("iter = %i\trow = %i\t row in bin = %.2b\tcol = %i\tcol in bin = %.2b\n", i, E2BITS(temp6bit), E2BITS(temp6bit), C4BITS(temp6bit), C4BITS(temp6bit));
		ft_printf("nb = %i\nin bin = %.4b\n\n", six_to_four[i][C4BITS(temp6bit) + 16 * E2BITS(temp6bit)], six_to_four[i][C4BITS(temp6bit) + 16 * E2BITS(temp6bit)]);
		


		temp = temp | six_to_four[i][(C4BITS(temp6bit)) | (16 * E2BITS(temp6bit))];
	}
	ft_printf("----------------------- check example after S1\n01011100100000101011010110010111\n%.32b\n----------------------- finish this check\n", temp);











	return (ft_strdup("res"));
}

int		ft_print_usage(void)
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (1);
}

