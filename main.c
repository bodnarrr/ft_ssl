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

// int		ft_base64(int ac, char **av, t_ssl_cmds *cmds)
// {
// 	ft_printf("base64 working\n");
// 	return (1);
// }

int		ft_desecb(int ac, char **av, t_ssl_cmds *cmds)
{
	ft_printf("desecb working\n");
	return (1);
}

int		ft_descbc(int ac, char **av, t_ssl_cmds *cmds)
{
	ft_printf("descbc working\n");
	return (1);
}


int		main(int ac, char **av)
{
	t_ssl_cmds	*cmds;
	int			ret;

	if (ac == 1)
		return(ft_print_usage());
	cmds = ft_ssl_get_commands(ac, av);
	// ft_printf("mode = %d\nencr = %d\ndecr = %d\nin = %d\ninpos = %d\nout = %d\noutpos = %d\nkey = %d\nkeypos = %d\nbase64 = %d\nsz_bs64 = %d\n\n", cmds->mode, cmds->encr, cmds->decr, cmds->in, cmds->inpos, cmds->out, cmds->outpos, cmds->key, cmds->keypos, cmds->base64, cmds->sz_bs64);
	if (cmds->mode == 0)
		return(ft_ssl_error(av[1], &cmds));
	if (cmds->mode == 1)
		ret = ft_base64(ac, av, cmds);
	if (cmds->mode == 2)
		ret = ft_desecb(ac, av, cmds);
	if (cmds->mode == 3)
		ret = ft_descbc(ac, av, cmds);
	free(cmds);
	return (ret);
}