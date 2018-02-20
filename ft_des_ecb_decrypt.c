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

#include "../includes/ft_ssl_des.h"

char			*ft_filled_by_len(char *input)
{
	size_t		len;
	int			i;
	char		*res;

	len = ft_strlen(input);
	if (len == 0)
		return (ft_strdup(EIGHTED));
	else if (len >= 8)
		return (ft_strsub(input, 0, 8));
	else
	{
		res = ft_strnew(8);
		i = 8 - len;
		res = ft_memset(res, i, 8);
		res = ft_memcpy(res, (const void*)input, len);
		return (res);
	}
}

char			*ft_string_from_bits_rev(uint64_t inf, size_t *output)
{
	char		*res;
	int			size;
	uint8_t		temp;
	int			i;

	size = 8;
	if ((inf & 255) >= 1 || (inf & 255) <= 7)
		size = 8 - (inf & 255);
	*output += size;
	res = ft_strnew(size);
	i = -1;
	while (++i < size)
	{
		temp = (inf >> (56 - i * 8)) & 255;
		res[i] = temp;
	}
	return (res);
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
		res = res | g_six_to_four[i][(CENTR4OF6(temp)) | ((FL2OF6(temp)) << 4)];
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

uint64_t		ft_shuffle_key_rev(uint64_t key, uint8_t i)
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
	left = (left >> i) | ((left & clear) << (28 - i));
	right = (right >> i) | ((right & clear) << (28 - i));
	return (JOINBITS(left, right, 28));
}

uint64_t		ft_des_permut(uint64_t nb, uint8_t prm[], int new_sz, int curr_sz)
{
	int			i;
	uint64_t	res;

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
	while (++i < 16)
	{
		res <<= 4;
		if (key[i])
		{
			if (key[i] >= '0' && key[i] <= '9')
				res = res | (key[i] - '0');
			if (key[i] >= 'A' && key[i] <= 'F')
				res = res | (key[i] - 55);
			if (key[i] >= 'a' && key[i] <= 'f')
				res = res | (key[i] - 87);
		}
	}
	ft_strdel(&key);
	return (res);
}

char			*ft_decoding_des(char *input, uint64_t key, size_t *output)
{
	uint64_t	converted;
	int			i;
	uint64_t	left;
	uint64_t	left_new;
	uint64_t	right;

	i = -1;
	converted = ft_input_to_bits(input);
	// converted = 6506523155595102834;
	converted = ft_des_permut(converted, g_initial_shuffle, 64, 64);
	key = ft_des_permut(key, g_pc1, 56, 64);
	key = ft_shuffle_key(key, 1);
	while (++i < 16)
	{
		left = L32OF64(converted);
		left_new = R32OF64(converted);
		right = R32OF64(converted);
		right = ft_des_permut(right, g_expand_right, 48, 32);
		key = ft_shuffle_key_rev(key, g_key_shift[i]);
		right ^= ft_des_permut(key, g_pc2, 48, 56);
		right = ft_des_permut(ft_s_boxes(right), g_p_permut, 32, 32);
		right ^= left;
		converted = JOINBITS(left_new, right, 32);
	}
	converted = (R32OF64(converted) << 32) | (L32OF64(converted));
	return (ft_string_from_bits_rev(ft_des_permut(converted, g_finish, 64, 64), output));
}

char			*ft_des_ecb_decrypt(char *input, char *key, size_t *output)
{
	char		*res;
	char		*temp;
	char		*fordel;
	uint64_t 	bit_key;

	res = ft_strnew(0);
	bit_key = ft_key_to_bits(ft_strdup(key));
	while (*input)
	{
		temp = ft_decoding_des(input, bit_key, output);
		fordel = res;
		res = ft_strjoin(res, temp);
		ft_strdel(&temp);
		input += 8;
	}
	return (res);
}

int				main(int ac, char **av)
{
	size_t		output;
	char		*res;

	if (ac < 2)
		return (1);
	output = 0;
	res = ft_des_ecb_decrypt(av[1], av[2], &output);
	write(1, res, output);
	return (0);
}
