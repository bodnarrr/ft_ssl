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

	if (!cmds->decr)
		res_str = ft_base64_encode(ac, av, cmds);
	else
		res_str = ft_base64_decode(ac, av, cmds);
	if (res_str == NULL)
	{
		ft_strdel(&res_str);
		return (1);
	}
	ft_ssl_write(av, &res_str, cmds);
	return (0);
}
