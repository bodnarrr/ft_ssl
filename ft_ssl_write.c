/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:10:47 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/22 19:10:47 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

void			ft_ssl_write(char **av, char **str, t_ssl_cmds *cmds)
{
	int			fd;

	// ft_printf("output = %d\n", cmds->size_output);
	fd = 1;
	if (cmds->out)
		fd = open(av[cmds->outpos], O_WRONLY | O_CREAT, 0777);
	write(fd, *str, cmds->size_output);
	if (cmds->encr && cmds->mode == 1)
		write(fd, "\n", 1);
	ft_strdel(str);
	*str = NULL;
	close(fd);
}
