/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_join_block.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:18:28 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/22 14:18:28 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

char		*ft_des_join_block(char *curr, char *block, t_ssl_cmds *cmds)
{
	char	*res;
	char	*ret;
	int		i;

	res = ft_strnew(cmds->size_output + 8);
	ret = res;
	i = -1;
	while (++i < cmds->size_output)
	{
		*res = *curr;
		res++;
		curr++;
	}
	i = -1;
	while (++i < 8)
	{
		*res = *block;
		res++;
		block++;
	}
	return (ret);
}
