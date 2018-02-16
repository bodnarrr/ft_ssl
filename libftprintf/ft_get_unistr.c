/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_unistr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:52:27 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/25 15:52:28 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char				*ft_get_unistr(va_list ap)
{
	unsigned int	*nbrs;
	char			*res;
	char			*temp;
	char			*fordel;

	res = ft_strnew(0);
	nbrs = va_arg(ap, unsigned int*);
	if (!nbrs)
		return (ft_strdup("(null)"));
	while (*nbrs)
	{
		temp = ft_get_unichar(*nbrs);
		fordel = res;
		res = ft_strjoin(res, temp);
		ft_strdel(&fordel);
		ft_strdel(&temp);
		nbrs++;
	}
	return (res);
}
