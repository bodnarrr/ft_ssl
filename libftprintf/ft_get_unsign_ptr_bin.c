/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_unsign_ptr_bin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 12:00:50 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/17 12:01:03 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*ft_get_binary(va_list ap)
{
	char	*temp;

	temp = ft_itoa_base_unsign(va_arg(ap, uintmax_t), 2);
	return (temp);
}

char		*ft_get_unsign(t_params *params, va_list ap)
{
	char	*temp;

	if (params->len >= 32)
		temp = ft_itoa_base_unsign(va_arg(ap, uintmax_t), 10);
	else if (params->len >= 16)
		temp = ft_itoa_base_unsign(va_arg(ap, size_t), 10);
	else if (params->len >= 8)
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned long long int), 10);
	else if (params->len >= 4)
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned long int), 10);
	else if (params->len >= 2)
		temp = ft_itoa_base_unsign((unsigned short)va_arg(ap, int), 10);
	else if (params->len >= 1)
		temp = ft_itoa_base_unsign((unsigned char)va_arg(ap, int), 10);
	else
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned int), 10);
	return (temp);
}

char		*ft_get_longunsign(t_params *params, va_list ap)
{
	char	*temp;

	if (params->len >= 32)
		temp = ft_itoa_base_unsign(va_arg(ap, uintmax_t), 10);
	else if (params->len >= 16)
		temp = ft_itoa_base_unsign(va_arg(ap, size_t), 10);
	else if (params->len >= 8)
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned long long int), 10);
	else
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned long int), 10);
	return (temp);
}

char		*ft_get_ptr(t_params *params, va_list ap)
{
	char	*temp;
	char	*fordel;

	temp = ft_itoa_base_unsign(va_arg(ap, unsigned long int), 16);
	ft_apply_precision(&temp, params);
	if (!ft_strcmp(temp, "0") && params->dot && params->prec == 0)
		*temp = '\0';
	fordel = temp;
	temp = ft_strjoin("0x", temp);
	ft_strdel(&fordel);
	return (temp);
}

char		*ft_get_char_str_perc(char **temp, char conv, va_list ap)
{
	if (conv == 'c')
	{
		*temp = ft_strnew(1);
		**temp = va_arg(ap, int);
		if (**temp == 0)
			**temp = -100;
	}
	if (conv == 's')
	{
		*temp = ft_strdup(va_arg(ap, char*));
		if (!*temp)
			*temp = ft_strdup("(null)");
	}
	if (conv == '%')
	{
		*temp = ft_strnew(1);
		**temp = '%';
	}
	return (*temp);
}
