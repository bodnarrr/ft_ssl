/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_make_keyvector.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:08:22 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/26 14:08:25 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

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
	return (res);
}

uint64_t		ft_descbc_make_vector(char *str)
{
	int			i;
	uint64_t	res;

	res = 0;
	i = -1;
	while (++i < 8)
	{
		res <<= 8;
		res |= (str[i] & 255);
	}
	return (res);
}
