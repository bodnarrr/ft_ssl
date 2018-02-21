/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desecb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:13:50 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/20 13:13:51 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

int			ft_desecb(int ac, char **av, t_ssl_cmds *cmds)
{
	char	*res_str;

	if (!cmds->decr)
		res_str = ft_desecb_encode(ac, av, cmds);
	else
		res_str = ft_desecb_decode(ac, av, cmds);
	if (res_str == NULL)
	{
		ft_strdel(&res_str);
		return (1);
	}
	ft_ssl_write(av, &res_str, cmds);
	return (0);
}
