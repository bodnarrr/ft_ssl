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

#include "libftprintf.h"
#include "ft_des_globals.h"
#include "ft_ssl_des.h"

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
	uint8_t		temp;
	int			i;

	res = ft_strnew(8);
	i = -1;
	while (++i < 8)
	{
		temp = (inf >> (56 - i * 8)) & 255;
		// ft_printf("temp = %d\n", temp);
		res[i] = temp;
	}
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
	// ft_printf("key: %.56b\nhal: %.28b%.28b\n", key, left, right);
	// ft_printf("before shuffle: %.28b %.28b\n", left, right);

	left = (left << i & 0xFFFFFFF) | (left >> (28 - i) & clear);
	right = (right << i & 0xFFFFFFF) | (right >> (28 - i) & clear);
	// ft_printf("after  shuffle: %.28b %.28b\n", left, right);

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

uint64_t		ft_input_to_bits(char *str)
{
	uint64_t		res;
	int				i;

	res = 0;
	i = -1;
	while (++i < 8)
	{
		res <<= 8;
		res = res | *(str + i);
	}
	return (res);
}

uint64_t		ft_key_to_bits(char *key)
{
	uint64_t	res;
	int			i;
	int			temp;

	res = 0;
	i = -1;
	while(++i < 16)
	{
		res <<= 4;
		if (key[i])
		{
			// ft_printf("key[i] = %c\n", key[i]);
			if (key[i] >= '0' && key[i] <= '9')
				res = res | (key[i] - '0');
			if (key[i] >= 'A' && key[i] <= 'F')
				res = res | (key[i] - 55);
			if (key[i] >= 'a' && key[i] <= 'f')
				res = res | (key[i] - 87);
		}

	}
	// ft_printf("key in bits in F: %.64b\n", res);
	ft_strdel(&key);
	return (res);
}

char			*ft_encoding_des(char *input, uint64_t key)
{
	uint64_t	converted;
	int			i;
	uint64_t	left;
	uint64_t	left_new;
	uint64_t	right;

	i = -1;
	converted = ft_input_to_bits(input);
	// ft_printf("formed block: \"%s\"\n", input);
	// ft_printf("block in bits: %.64b\nnkolo in bits: 0101010101001110010010010101010000110100001100100011010000110010\n", converted);
	// ft_printf("key in bits: %.64b\n", key);
	// ft_printf("key in nkol: 0100001001000010010000100000000000000000000000000000000000000000\n");

	// converted = 81985529216486895; //just an example!`
	// ft_printf("======= check input in HEX=========\nin: 0123456789ABCDEF\nmy: 0%llX\n====================================================================\n\n", converted);
	// ft_printf("======= check input in binary=========\nin: 0000000100100011010001010110011110001001101010111100110111101111\nmy: %.64b\n====================================================================\n\n", converted);
	converted = ft_permut(converted, initial_shuffle, 64, 64);
	// ft_printf("init permut: %.64b\nnkol permut: 0000111111111001010110110000010100000000111100000000011010100010\n", converted);

	// ft_printf("======= check input after initial permute=========\nin: 1100110000000000110011001111111111110000101010101111000010101010\nmy: %.64b\n====================================================================\n\n", converted);
	// key = 1383827165325090801; //just an example!
	// ft_printf("======= check key on start=========\nin: 0001001100110100010101110111100110011011101111001101111111110001\nmy: %.64b\n====================================================================\n\n", key);
	key = ft_permut(key, pc1, 56, 64);
	// ft_printf("======= check key after PC1=========\nin: 11110000110011001010101011110101010101100110011110001111\nmy: %.48b\n====================================================================\n\n\n", key);

	while (++i < 16)
	{
		// ft_printf("Start of %i iteration\n", i);
		left = L32OF64(converted);
		left_new = R32OF64(converted);
		right = R32OF64(converted);
		// ft_printf("myR: %.32b\nnkR: 00000000111100000000011010100010\n", right);
		// ft_printf("myL: %.32b\nnkL: 00001111111110010101101100000101\n", left);

		// ft_printf("======= check right part=========\nin: 11110000101010101111000010101010\nmy: %.32b\n====================================================================\n\n", right);
		

		right = ft_permut(right, expand_right, 48, 32);
		// ft_printf("myRexp: %.48b\nnkRexp: 000000000001011110100000000000001101010100000100\n", right);

		// ft_printf("======= check extented right part=========\nin: 011110100001010101010101011110100001010101010101\nmy: %.48b\n====================================================================\n\n", right);
		key = ft_shuffle_key(key, key_shift[i]);
		// ft_printf("======= check shuffled key=========\nin: 11100001100110010101010111111010101011001100111100011110\nmy: %.56b\n====================================================================\n", key);
		// ft_printf("mySubK: %.48b\nnkSubK: 100000001000000000000010000000000010000010000000\n", ft_permut(key, pc2, 48, 56));

		right = right ^ ft_permut(key, pc2, 48, 56);
		// ft_printf("======= check right after XOR with key=========\nin: 011000010001011110111010100001100110010100100111\nmy: %.48b\n====================================================================\n", right);
		right = ft_s_boxes(right);
		
		right = ft_permut(right, p_permut, 32, 32);
		// ft_printf("======= check right after P permutation=========\nin: 00100011010010101010100110111011\nmy: %.32b\n====================================================================\n", right);
		right = right ^ left;
		// ft_printf("======= check right after XOR with left=========\nin: 11101111010010100110010101000100\nmy: %.32b\n====================================================================\n", right);
		converted = JOINBITS(left_new, right, 32);
		// ft_printf("End of %i iteration\n\n\n", i);
	}
	// ft_printf("======= check left after 16 iterations=========\nin: 01000011010000100011001000110100\nmy: %.32b\n====================================================================\n\n", L32OF64(converted));
	// ft_printf("======= check right after 16 iterations=========\nin: 00001010010011001101100110010101\nmy: %.32b\n====================================================================\n\n", R32OF64(converted));
	
	converted =  (R32OF64(converted) << 32) | (L32OF64(converted));
	// ft_printf("======= check reversed result=========\nin: 0000101001001100110110011001010101000011010000100011001000110100\nmy: %.64b\n====================================================================\n\n", converted);
	// ft_printf("======= LAST check=========\nin: 1000010111101000000100110101010000001111000010101011010000000101\nmy: %.64b\nmy: %llX\nst: 85E813540F0AB405\n====================================================================\n\n", ft_permut(converted, finish, 64, 64), ft_permut(converted, finish, 64, 64));
	return (ft_string_from_bits(ft_permut(converted, finish, 64, 64)));
}

char			*ft_des_ecb(char *input, char *key, size_t *output)
{
	char		*res;
	char		*temp;
	char		*fordel;
	char		*for_work;
	t_desecb	inf;

	res = ft_strnew(0);
	inf.input_len = ft_strlen(input);
	inf.encryted = 0;
	inf.key = ft_key_to_bits(ft_strdup(key));
	while (inf.encryted <= inf.input_len)
	{
		// ft_printf("remaining str: %s\n", input);
		for_work = ft_filled_by_len(input);
		temp = ft_encoding_des(for_work, inf.key);
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

int 			main(int ac, char **av)
{
	size_t		output;
	char		*res;

	if (ac < 2)
		return (1);

	output = 0;

	res = ft_des_ecb(av[1], "424242", &output);
	write(1, res, output);

	return (0);
}
