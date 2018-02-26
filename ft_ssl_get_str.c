/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_get_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 18:42:49 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/22 18:42:50 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

char			*ft_get_str(char **av, t_ssl_cmds *cmds)
{
	char		*res;
	char		*fordel;
	char		buf[BUFF_SSL + 1];
	int			rd;
	int			fd;

	fd = 0;
	if (cmds->in && av[cmds->inpos])
		fd = open(av[cmds->inpos], O_RDONLY);
	if (fd == -1 && ft_printf("No such file or directory\n"))
		return (NULL);
	res = ft_strnew(0);
	while ((rd = read(fd, buf, BUFF_SSL)) > 0)
	{
		buf[rd] = '\0';
		fordel = res;
		res = ft_ssl_join_block(res, buf, cmds->len_to_code, rd);
		cmds->len_to_code += rd;
		ft_strdel(&fordel);
		ft_bzero(buf, BUFF_SSL);
	}
	if (rd == -1 && ft_printf("Ha-ha! I can't encrypt directory!\n"))
		return (NULL);
	return (res);
}
