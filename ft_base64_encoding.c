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

void			ft_base64_write(char **av, char *str, t_ssl_cmds *cmds)
{
	int			fd;

	ft_printf("str in write = %s\n", str);
	fd = 1;
	if (cmds->out)
		fd = open(av[cmds->outpos], O_WRONLY | O_CREAT, 0777);
	write(fd, str, cmds->sz_bs64);
	write(fd, "\n", 1);
	ft_strdel(&str);
	close(fd);
}

uint32_t		ft_str_to_32bits(char *str)
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

char			*ft_base64_encode_block(char *str)
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

int				ft_base64_encode(int ac, char **av, t_ssl_cmds *cmds, int *ret)
{
	int			fd;
	int			rd;
	char		buf[BS64EN + 1];
	char		*res;

	fd = 0;
	if (cmds->in)
		fd = open(av[cmds->inpos], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("No such file or directory\n");
		return (1);
	}
	res = ft_strnew(0);
	while ((rd = read(fd, buf, BS64EN)) > 0)
	{
		buf[rd] = '\0';
		ft_base64_join_block(&res, buf, cmds);
		ft_bzero(buf, BS64EN + 1);
		cmds->sz_bs64 += 4;
	}
	close(fd);
	ft_base64_write(av, res, cmds);
	return (*ret);
}
