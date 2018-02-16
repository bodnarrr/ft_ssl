/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typical_or_unicode_arg.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:57:15 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/29 18:57:19 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*ft_typical_arg(t_params *params, va_list ap)
{
	char	*temp;

	temp = NULL;
	if (params->conv == 'i' || params->conv == 'd')
		temp = ft_get_int(params, ap);
	else if (params->conv == 'D')
		temp = ft_get_longint(params, ap);
	else if (params->conv == 'o')
		temp = ft_get_octal(params, ap);
	else if (params->conv == 'O')
		temp = ft_get_longoctal(params, ap);
	else if (params->conv == 'x' || params->conv == 'X')
		temp = ft_get_hexadec(params, ap);
	else if (params->conv == 'u')
		temp = ft_get_unsign(params, ap);
	else if (params->conv == 'U')
		temp = ft_get_longunsign(params, ap);
	else if (params->conv == 'p')
		temp = ft_get_ptr(params, ap);
	return (temp);
}

char		*ft_unicode_arg(t_params *params, va_list ap)
{
	char	*temp;
	uint	for_uni;

	temp = NULL;
	if (params->conv == 'C' || (params->conv == 'c' && params->len >= 4
		&& params->len < 8))
	{
		if (MB_CUR_MAX != 4 && (temp = ft_strnew(1)) != NULL)
			temp[0] = (char)va_arg(ap, int);
		else
		{
			for_uni = va_arg(ap, uint);
			temp = ft_get_unichar(for_uni);
		}
	}
	else if (params->conv == 'S' || (params->conv == 's' && params->len >= 4
		&& params->len < 8))
		temp = ft_get_unistr(ap);
	return (temp);
}
