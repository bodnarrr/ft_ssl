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

#define CENTR4OF6(x)		((x) >> 1 & 15)
#define FL2OF6(x) 			((x & 1) | (x >> 4 & 2))
#define L32OF64(x)			((x) >> 32)
#define R32OF64(x)			((x) & 0xFFFFFFFF)
#define L28OF56(x)			((x) >> 28)
#define R28OF56(x)			((x) & 0xFFFFFFF)
#define JOINBITS(x, y, sz)	((x << sz) | y)
#define EIGHTED 			"\b\b\b\b\b\b\b\b"

typedef struct	s_desecb
{
	size_t		input_len;
	size_t		encryted;
}				t_desecb;

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

uint8_t six_to_four1[64] =
	{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
	0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
	4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
	15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};

uint8_t six_to_four2[64] =
	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
	3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
	0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
	13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};

uint8_t six_to_four3[64] =
	{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
	13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
	13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
	1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12};

uint8_t six_to_four4[64] =
	{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
	13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
	10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
	3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};

uint8_t six_to_four5[64] =
	{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
	14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
	4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
	11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};

uint8_t six_to_four6[64] =
	{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
	10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
	9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
	4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};

uint8_t six_to_four7[64] = 
	{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
	13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
	1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
	6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};

uint8_t six_to_four8[64] =
	{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
	1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
	7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
	2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};		

uint8_t *(six_to_four[]) =
	{six_to_four1,	six_to_four2, six_to_four3, six_to_four4,
	six_to_four5, six_to_four6, six_to_four7, six_to_four8};

uint8_t p_permut[32] =
	{16, 7, 20, 21,
	29, 12, 28, 17,
	1, 15, 23, 26,
	5, 18, 31, 10,
	2, 8, 24, 14,
	32, 27, 3, 9,
	19, 13, 30, 6,
	22, 11, 4, 25};

uint8_t finish[64] =
	{40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41 ,9, 49, 17, 57, 25};

char			*ft_filled_by_len(char *input)
{
	size_t		len;
	int			i;
	char		*res;

	len = ft_strlen(input);
	if (len == 0)
		return(ft_strdup(EIGHTED));
	else if (len >= 8)
		return (ft_strsub(input, 0, 8));
	else
	{
		res = ft_strnew(8);
		i = 8 - len;
		res = ft_memset(res , i, 8);
		res = ft_memcpy(res, (const void*)input, len);
		return (res);
	}
}

char			*ft_string_from_bits(uint64_t inf)
{
	char		*res;
	int			i;

	res = ft_strnew(8);
	i = -1;
	while (++i < 8)
		res[i] = inf >> (56 - i * 8) & 255;
	return(res);
}

uint64_t		ft_s_boxes(uint64_t inf)
{
	int			i;
	uint64_t	res;
	uint64_t	temp;

	res = 0;
	i = -1;
	while (++i < 8)
	{
		res <<= 4;
		temp = inf >> (42 - i * 6) & 63;
		res = res | six_to_four[i][(CENTR4OF6(temp)) | ((FL2OF6(temp)) << 4)];
	}
	return (res);
}

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
	uint64_t	converted;
	int			i;
	uint64_t	left;
	uint64_t	left_new;
	uint64_t	right;

	i = -1;
	converted = ft_input_to_bits(input);
	converted = 81985529216486895; //just an example!
	ft_printf("======= check input in binary=========\nin: 0000000100100011010001010110011110001001101010111100110111101111\nmy: %.64b\n====================================================================\n\n", converted);
	converted = ft_permut(converted, initial_shuffle, 64, 64);
	ft_printf("======= check input after initial permute=========\nin: 1100110000000000110011001111111111110000101010101111000010101010\nmy: %.64b\n====================================================================\n\n", converted);
	key = 1383827165325090801; //just an example!
	ft_printf("======= check key on start=========\nin: 0001001100110100010101110111100110011011101111001101111111110001\nmy: %.64b\n====================================================================\n\n", key);
	key = ft_permut(key, pc1, 56, 64);
	ft_printf("======= check key after PC1=========\nin: 11110000110011001010101011110101010101100110011110001111\nmy: %.48b\n====================================================================\n\n\n", key);

	while (++i < 16)
	{
		ft_printf("Start of %i iteration\n", i);
		left = L32OF64(converted);
		left_new = R32OF64(converted);
		right = R32OF64(converted);
		ft_printf("======= check right part=========\nin: 11110000101010101111000010101010\nmy: %.32b\n====================================================================\n\n", right);
		right = ft_permut(right, expand_right, 48, 32);
		ft_printf("======= check extented right part=========\nin: 011110100001010101010101011110100001010101010101\nmy: %.48b\n====================================================================\n\n", right);
		key = ft_shuffle_key(key, key_shift[i]);
		ft_printf("======= check shuffled key=========\nin: 11100001100110010101010111111010101011001100111100011110\nmy: %.48b\n====================================================================\n", key);
		key = ft_permut(key, pc2, 48, 56);
		ft_printf("======= check 48 key after PC2=========\nin: 000110110000001011101111111111000111000001110010\nmy: %.48b\n====================================================================\n", key);
		right = right ^ key;
		ft_printf("======= check right after XOR with key=========\nin: 011000010001011110111010100001100110010100100111\nmy: %.48b\n====================================================================\n", right);
		right = ft_s_boxes(right);
		ft_printf("======= check right after S boxes=========\nin: 01011100100000101011010110010111\nmy: %.32b\n====================================================================\n", right);
		right = ft_permut(right, p_permut, 32, 32);
		ft_printf("======= check right after P permutation=========\nin: 00100011010010101010100110111011\nmy: %.32b\n====================================================================\n", right);
		right = right ^ left;
		ft_printf("======= check right after XOR with left=========\nin: 11101111010010100110010101000100\nmy: %.32b\n====================================================================\n", right);
		converted = JOINBITS(left_new, right, 32);
		ft_printf("End of %i iteration\n\n\n", i);
	}
	ft_printf("======= check left after 16 iterations=========\nin: 01000011010000100011001000110100\nmy: %.32b\n====================================================================\n", L32OF64(converted));
	converted =  (R32OF64(converted) << 32) | (L32OF64(converted));
	return (ft_string_from_bits(ft_permut(converted, finish, 64, 64)));
}

char			*ft_des_ecb(char *input, uint64_t key, size_t *output)
{
	char		*res;
	char		*temp;
	char		*fordel;
	char		*for_work;
	t_desecb	inf;

	res = ft_strnew(0);
	ft_bzero(&inf, sizeof(t_desecb));
	inf.input_len = ft_strlen(input);
	while (inf.encryted <= inf.input_len)
	{
		for_work = ft_filled_by_len(input);
		temp = ft_encoding_des(for_work, key);
		fordel = res;
		res = ft_strjoin(res, temp);
		ft_strdel(&temp);
		ft_strdel(&for_work);
		inf.encryted += 8;
		input += 8;
		*output += 8;
	}
	return (res);
}



int 	main(int ac, char **av)
{
	size_t	output;
	char	*res;

	if (ac < 2)
		return (1);
	output = 0;
	res = ft_des_ecb(av[1], 0x128, &output);
	write(1, res, output);
	return (0);
}
