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
	int		ret;

	ret = 0;
	if (!cmds->decr)
		ret = ft_base64_encode(ac, av, cmds);
	else
		ret = ft_base64_decode(ac, av, cmds);
	return (ret);
}
