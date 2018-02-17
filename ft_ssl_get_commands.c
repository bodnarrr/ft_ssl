/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_get_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 13:57:44 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/16 13:57:45 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static uint		ft_ssl_check_mode(char *str)
{
	uint		mode;

	mode = 0;
	if (ft_strequ(str, "base64"))
		mode = 1;
	if (ft_strequ(str, "des-ecb"))
		mode = 2;
	if (ft_strequ(str, "des") || ft_strequ(str, "des-cbc"))
		mode = 3;
	return (mode);
}

t_ssl_cmds		*ft_ssl_get_commands(int ac, char **av)
{
	t_ssl_cmds	*cmds;
	int			i;

	cmds = (t_ssl_cmds*)malloc(sizeof(t_ssl_cmds));
	ft_bzero(cmds, sizeof(t_ssl_cmds));
	cmds->sz_bs64 = 0;
	i = 2;
	cmds->mode = ft_ssl_check_mode(av[1]);
	while (i < ac)
	{
		if (ft_strequ(av[i], "-e"))
			cmds->encr = 1;
		if (ft_strequ(av[i], "-d"))
			cmds->decr = 1;
		if ((ft_strequ(av[i], "-k") || ft_strequ(av[i], "-K")) && (cmds->key = 1) == 1)
			cmds->keypos = i + 1;
		if (ft_strequ(av[i], "-i") && (cmds->in = 1) == 1)
			cmds->inpos = i + 1;
		if (ft_strequ(av[i], "-o") && (cmds->out = 1) == 1)
			cmds->outpos = i + 1;
		if (ft_strequ(av[i], "-a"))
			cmds->base64 = 1;
		i++;
	}
	return (cmds);
}
