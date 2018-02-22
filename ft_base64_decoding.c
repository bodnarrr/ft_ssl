/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64_decoding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:23:54 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/19 15:23:55 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

static char		*ft_base64_decode_block(char *str, t_ssl_cmds *cmds)
{
	uint32_t	conv;
	int			i;
	int			j;
	char		*ret;

	ret = ft_strnew(3);
	i = -1;
	conv = 0;
	while (++i < 4)
	{
		j = 0;
		if (*(str + i) != '=')
			while (*(str + i) != g_base64[j] && j < 64)
				j++;
		conv |= j;
		conv <<= 6;
	}
	conv <<= 2;
	i = -1;
	while (++i < 3)
		ret[i] = conv >> (24 - 8 * i) & 255;
	cmds->size_output += ft_strlen(ret);
	return (ret);
}

static char		*ft_base64_decode_all(char *crypted, t_ssl_cmds *cmds)
{
	char		*res;
	char		*fordel;
	char		*temp;

	res = ft_strnew(0);
	cmds->len_to_code = ft_strlen(crypted);
	while (cmds->len_coded < cmds->len_to_code)
	{
		if (*crypted == '\n' && (cmds->len_coded % 65 == 64
			|| ft_strlen(crypted) == 1))
		{
			crypted++;
			cmds->len_coded += 1;
			continue ;
		}
		fordel = res;
		temp = ft_base64_decode_block(crypted, cmds);
		res = ft_strjoin(res, temp);
		ft_strdel(&fordel);
		ft_strdel(&temp);
		crypted += 4;
		cmds->len_coded += 4;
	}
	return (res);
}

static int		ft_base64_check_input(char *str)
{
	int			i;
	int			j;
	int			len;

	len = ft_strlen(str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_strchr(g_base64, str[i]))
		{
			if ((i % 65 == 64 || i == len - 1) && str[i] == '\n')
				j++;
			else if (str[i] == '=' && (i == len - 1 || i == len - 2))
				;
			else if (str[i] == '=' && str[len - 1] == '\n'
				&& (i == len - 2 || i == len - 3))
				;
			else
				return (0);
		}
		i++;
	}
	if ((len - j) % 4 != 0)
		return (0);
	return (1);
}

char			*ft_base64_decode(int ac, char **av, t_ssl_cmds *cmds)
{
	char		*for_work;
	char		*decrypted;

	for_work = ft_get_str(ac, av, cmds);
	if (!for_work)
		return (NULL);
	if (!ft_base64_check_input(for_work))
	{
		ft_strdel(&for_work);
		ft_printf("Incorrect input!\n");
		return (NULL);
	}
	decrypted = ft_base64_decode_all(for_work, cmds);
	return (decrypted);
}
