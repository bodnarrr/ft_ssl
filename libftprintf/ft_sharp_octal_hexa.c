/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sharp_octal_hexa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:34:49 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/29 16:34:50 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_sharp_octal_hexa(char **str, t_params *params)
{
	char	*fordel;

	if (params->conv == 'x' && params->prec != 0 && ft_strcmp(*str, "0"))
	{
		fordel = *str;
		*str = ft_strjoin("0x", *str);
		ft_strdel(&fordel);
	}
	else if (params->conv == 'X' && params->prec != 0 && ft_strcmp(*str, "0"))
	{
		fordel = *str;
		*str = ft_strjoin("0X", *str);
		ft_strdel(&fordel);
	}
	else if ((params->conv == 'o' || params->conv == 'O')
		&& ft_strcmp(*str, "0"))
	{
		fordel = *str;
		*str = ft_strjoin("0", *str);
		ft_strdel(&fordel);
	}
}
