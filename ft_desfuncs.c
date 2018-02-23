/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desfuncs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 18:25:34 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/20 18:25:35 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

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
		res[i] = temp;
	}
	i = -1;
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
