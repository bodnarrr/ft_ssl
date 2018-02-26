/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64_encoding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 14:55:09 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/19 14:55:09 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

static uint32_t	ft_str_to_32bits(char *str)
{
	int			i;
	uint32_t	ret;

	i = 0;
	ret = 0;
	while (*str)
	{
		ret <<= 8;
		ret |= str[i];
		str++;
	}
	return (ret);
}

static char		*ft_base64_encode_block(char *str, t_ssl_cmds *cmds)
{
	uint32_t	conv;
	int			i;
	char		*ret;
	char		*cpy;

	ret = ft_strnew(4);
	i = -1;
	conv = 0;
	while (++i < 3)
	{
		conv <<= 8;
		if (str[i])
			conv |= (str[i] & 255);
	}
	i = -1;
	while (++i < 4)
		ret[i] = g_base64[(conv >> (18 - 6 * i)) & 63];
	if (cmds->last_iter && cmds->len_to_code - cmds->len_coded < 3)
		ret[3] = '=';
	if (cmds->last_iter && cmds->len_to_code - cmds->len_coded < 2)
		ret[2] = '=';
	return (ret);
}

char			*ft_base64_encode_all(char *input, t_ssl_cmds *cmds)
{
	char		*res;
	char		*fordel;
	char		*temp;

	if (cmds->base64)
	{
		cmds->len_coded = 0;
		cmds->len_to_code = cmds->size_output;
		cmds->size_output = 0;
	}
	res = ft_strnew(0);
	while (cmds->len_coded < cmds->len_to_code)
	{
		if (cmds->len_to_code - cmds->len_coded <= 3)
			cmds->last_iter = 1;
		fordel = res;
		temp = ft_base64_encode_block(input, cmds);
		res = ft_ssl_join_block(res, temp, cmds->size_output, 4);
		ft_strdel(&fordel);
		ft_strdel(&temp);
		input += 3;
		cmds->len_coded += 3;
		cmds->size_output += 4;
	}
	return (res);
}
