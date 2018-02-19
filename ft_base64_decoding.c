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

char			*ft_base64_decode_block(char *str)
{
	uint32_t	conv;
	int			i;
	int			j;
	char		*ret;

	ret = ft_strnew(3);
	i = -1;
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
	return (ret);
}

int				ft_base64_decode(int ac, char **av, t_ssl_cmds *cmds, int *ret)
{
	int			fd;
	int			rd;
	char		buf[BS64DE + 1];
	char		*res;

	fd = 0;
	if (cmds->in)
		fd = open(av[cmds->inpos], O_RDONLY);
	if (fd == -1 && ft_printf("No such file or directory\n"))
		return (1);
	res = ft_strnew(0);
	while ((rd = read(fd, buf, BS64DE)) > 0)
	{
		buf[rd] = '\0';
		if (ft_strequ(buf, "\n"))
			break ;
		ft_base64_join_block(&res, buf, cmds);
		ft_bzero(buf, BS64EN + 1);
	}
	if (rd != 0 && !ft_strequ(buf, "\n") && !close(fd))
	{
		ft_printf("\nIncorrect input!\n");
		ft_strdel(&res);
		return (1);
	}
	ft_base64_write(av, res, cmds);
	return (*ret);
}
