/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_from_bits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:03:05 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/26 18:03:06 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

char			*ft_string_from_bits_r(uint64_t inf, t_ssl_cmds *cmds)
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
	cmds->curr_block = 8;
	return (res);
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
