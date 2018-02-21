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
	int		ret;

	ret = 0;
	if (!cmds->decr)
		ret = ft_desecb_encode(ac, av, cmds);
	else
		ret = ft_desecb_decode(ac, av, cmds);
	return (ret);
}
