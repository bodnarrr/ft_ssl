/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 16:09:11 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/09 16:09:11 by abodnar          ###   ########.fr       */
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

#define CENTR4OF6(x)		x >> 1 & 15
#define FL2OF6(x) 			(x & 1) | (x >> 4 & 2)
#define L32OF64(x)			x >> 32
#define R32OF64(x)			x & 0xFFFFFFFF
#define L28OF56(x)			x >> 28
#define R28OF56(x)			x & 0xFFFFFFF
#define JOINBITS(x, y, sz)	(x << sz) | y

uint8_t initial_shuffle[64] =
	{58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7};

uint8_t pc1[56] =
	{57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4};

uint8_t expand_right[48] = 
	{32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1};

uint8_t key_shift[16] =
	{1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

uint8_t pc2[48] = 
	{14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32};

uint64_t		ft_shuffle_key(uint64_t key, uint8_t i)
{
	uint64_t	res;
	uint64_t	left;
	uint64_t	right;
	int			clear;

	res = 0;
	if (i == 1)
		clear = 1;
	else if (i == 2)
		clear = 3;
	left = L28OF56(key);
	right = R28OF56(key);
	left = (left << i & 0xFFFFFFF) | (left >> (28 - i) & clear);
	right = (right << i & 0xFFFFFFF) | (right >> (28 - i) & clear);
	return (JOINBITS(left, right, 28));
}

uint64_t		ft_permut(uint64_t nb, uint8_t prm[], int new_sz, int curr_sz)
{
	int			i;
	uint64_t 	res;

	i = -1;
	res = 0;
	while (++i < new_sz)
	{
		res <<= 1;
		res = res | ((nb >> (curr_sz - prm[i])) & 1);
	}
	return (res);
}

uint64_t	ft_input_to_bits(char *str)
{
	uint64_t	res;
	int			i;

	res = 0;
	i = -1;
	while (++i < 8)
	{
		res <<= 8;
		res = res | *(str + i);
	}
	return (res);
}

char	*ft_encoding_des(char *input, uint64_t key)
{
	char		*res;
	uint64_t	converted;
	int			i;
	int			j;
	uint64_t	left;
	uint64_t	left_new;
	uint64_t	right;

	ft_printf("===== first key check\nmy: %.64b\nst: 0001001100110100010101110111100110011011101111001101111111110001\n\n", key);


	i = -1;
	converted = ft_input_to_bits(input);
	converted = ft_permut(converted, initial_shuffle, 64, 64);
	key = ft_permut(key, pc1, 56, 64);
	ft_printf("===== key check after permute\nmy: %.56b\nst: 11110000110011001010101011110101010101100110011110001111\n\n", key);

	left = L32OF64(converted);
	while (++i < 16)
	{
		left_new = R32OF64(converted);
		right = ft_permut(R32OF64(converted), expand_right, 48, 32);
		right = right ^ ft_permut(ft_shuffle_key(key, key_shift[i]), pc2, 48, 56);
		


		converted = JOINBITS(left_new, right, 32);
	}
	return (ft_strdup("OK"));
}

char		*ft_des_ebc(char *input, uint64_t key)
{
	char	*res;
	char	*temp;
	char	*fordel;
	size_t	len;

	res = ft_strnew(0);
	temp = ft_encoding_des(input, key);
	// while ()
	// {
	// 	if (ft_strlen(input) > 8)
	// 		temp = ft_encoding_des(input, key);
	// 	else if (ft_strlen(input) < 8 && ft_strlen(input) > 0)
	// 		temp = ft_encoding_des(ft_filled_by_len(input), key);
	// 	else
	// 		temp = ft_encoding_des(EIGHTED STRING);
	// 	fordel = res;
	// 	res = ft_strjoin(res, temp);
	// 	ft_strdel(&temp);
	// }
	return (res);
}



int 	main(int ac, char **av)
{
	ft_printf("res = %s\n", ft_des_ebc("testtest", 0x133457799BBCDFF1));
	return (0);
}
