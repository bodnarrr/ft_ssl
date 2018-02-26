/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:23:06 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/30 13:23:07 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

int			ft_base64(int ac, char **av, t_ssl_cmds *cmds)
{
	char	*res_str;
	char	*for_work;

	for_work = ft_get_str(ac, av, cmds);
	if (for_work == NULL)
		return (1);
	if (!cmds->decr)
		res_str = ft_base64_encode_all(for_work, cmds);
	else
	{
		if (!ft_base64_check_input(for_work))
		{
			ft_strdel(&for_work);
			ft_printf("Incorrect input!\n");
			return (1);
		}
		res_str = ft_base64_decode_all(for_work, cmds);
	}
	if (res_str == NULL)
	{
		ft_strdel(&res_str);
		return (1);
	}
	ft_ssl_write(av, &res_str, cmds);
	return (0);
}
