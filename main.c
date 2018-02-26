/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 11:44:51 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/16 11:44:52 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

int		main(int ac, char **av)
{
	t_ssl_cmds	*cmds;
	int			ret;

	if (ac == 1)
		return (ft_print_usage());
	cmds = ft_ssl_get_commands(ac, av);
	if (cmds->mode == 0)
		return (ft_ssl_error(av[1], &cmds));
	if (cmds->mode == 1)
		ret = ft_base64(av, cmds);
	if (cmds->mode == 2)
		ret = ft_desecb(av, cmds);
	if (cmds->mode == 3)
		ret = ft_descbc(av, cmds);
	free(cmds);
	return (ret);
}
