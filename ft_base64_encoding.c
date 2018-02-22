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

static char		*ft_base64_encode_block(char *str)
{
	uint32_t	conv;
	int			i;
	char		*ret;
	char		*cpy;
	int			sz;

	ret = ft_strnew(4);
	i = -1;
	conv = 0;
	while (++i < 3)
	{
		conv <<= 8;
		if (str[i])
			conv |= str[i];
	}
	i = -1;
	while (++i < 4)
		ret[i] = g_base64[(conv >> (18 - 6 * i)) & 63];
	sz = ft_strlen(str);
	if (sz < 3)
		ret[3] = '=';
	if (sz < 2)
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
	}
	res = ft_strnew(0);
	while (cmds->len_coded < cmds->len_to_code)
	{
		fordel = res;
		temp = ft_base64_encode_block(input);
		res = ft_strjoin(res, temp);
		ft_strdel(&fordel);
		ft_strdel(&temp);
		input += 3;
		cmds->len_coded += 3;
		cmds->size_output += 4;
	}
	return (res);
}

char			*ft_base64_encode(int ac, char **av, t_ssl_cmds *cmds)
{
	char		*for_work;
	char		*encrypted;

	for_work = ft_get_str(ac, av, cmds);
	if (!for_work)
		return (NULL);
	encrypted = ft_base64_encode_all(for_work, cmds);
	return (encrypted);
}
