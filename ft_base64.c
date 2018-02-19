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

void		ft_base64_join_block(char **res, char *buf, t_ssl_cmds *cmds)
{
	char	*temp;
	char	*fordel;

	if (cmds->encr)
		temp = ft_base64_encode_block(buf);
	if (cmds->decr)
	{
		temp = ft_base64_decode_block(buf);
		cmds->sz_bs64 += ft_strlen(temp);
	}
	fordel = *res;
	*res = ft_strjoin(*res, temp);
	ft_strdel(&temp);
	ft_strdel(&fordel);
}

int			ft_base64(int ac, char **av, t_ssl_cmds *cmds)
{
	int		ret;

	ret = 0;
	if (!cmds->decr)
		ft_base64_encode(ac, av, cmds, &ret);
	else
		ft_base64_decode(ac, av, cmds, &ret);
	return (ret);
}
