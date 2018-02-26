/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_join_block.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 11:57:30 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/23 11:57:31 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

char		*ft_ssl_join_block(char *str, char *block, int sz1, int sz2)
{
	char	*res;
	char	*ret;

	res = ft_strnew(sz1 + sz2);
	ret = res;
	while (sz1--)
	{
		*res = *str;
		res++;
		str++;
	}
	while (sz2--)
	{
		*res = *block;
		res++;
		block++;
	}
	return (ret);
}
