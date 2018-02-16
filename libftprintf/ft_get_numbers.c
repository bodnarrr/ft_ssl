/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 17:35:45 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/16 17:35:46 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*ft_get_int(t_params *params, va_list ap)
{
	char	*temp;

	if (params->len >= 32)
		temp = ft_itoa_base_sign(va_arg(ap, intmax_t), 10);
	else if (params->len >= 16)
		temp = ft_itoa_base_sign(va_arg(ap, ssize_t), 10);
	else if (params->len >= 8)
		temp = ft_itoa_base_sign(va_arg(ap, long long int), 10);
	else if (params->len >= 4)
		temp = ft_itoa_base_sign(va_arg(ap, long int), 10);
	else if (params->len >= 2)
		temp = ft_itoa_base_sign((short)va_arg(ap, int), 10);
	else if (params->len >= 1)
		temp = ft_itoa_base_sign((char)va_arg(ap, int), 10);
	else
		temp = ft_itoa_base_sign(va_arg(ap, int), 10);
	return (temp);
}

char		*ft_get_longint(t_params *params, va_list ap)
{
	char	*temp;

	if (params->len >= 32)
		temp = ft_itoa_base_sign(va_arg(ap, intmax_t), 10);
	else if (params->len >= 16)
		temp = ft_itoa_base_unsign(va_arg(ap, size_t), 10);
	else if (params->len >= 8)
		temp = ft_itoa_base_sign(va_arg(ap, long long int), 10);
	else
		temp = ft_itoa_base_sign(va_arg(ap, long int), 10);
	return (temp);
}

char		*ft_get_octal(t_params *params, va_list ap)
{
	char	*temp;

	if (params->len >= 32)
		temp = ft_itoa_base_unsign(va_arg(ap, uintmax_t), 8);
	else if (params->len >= 16)
		temp = ft_itoa_base_unsign(va_arg(ap, size_t), 8);
	else if (params->len >= 8)
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned long long int), 8);
	else if (params->len >= 4)
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned long int), 8);
	else if (params->len >= 2)
		temp = ft_itoa_base_unsign((unsigned short)va_arg(ap, int), 8);
	else if (params->len >= 1)
		temp = ft_itoa_base_unsign((unsigned char)va_arg(ap, int), 8);
	else
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned int), 8);
	return (temp);
}

char		*ft_get_longoctal(t_params *params, va_list ap)
{
	char	*temp;

	if (params->len >= 32)
		temp = ft_itoa_base_unsign(va_arg(ap, intmax_t), 8);
	else if (params->len >= 16)
		temp = ft_itoa_base_unsign(va_arg(ap, size_t), 8);
	else if (params->len >= 8)
		temp = ft_itoa_base_unsign(va_arg(ap, long long int), 8);
	else
		temp = ft_itoa_base_unsign(va_arg(ap, long int), 8);
	return (temp);
}

char		*ft_get_hexadec(t_params *params, va_list ap)
{
	char	*temp;
	int		i;

	if (params->len >= 32)
		temp = ft_itoa_base_unsign(va_arg(ap, uintmax_t), 16);
	else if (params->len >= 16)
		temp = ft_itoa_base_unsign(va_arg(ap, size_t), 16);
	else if (params->len >= 8)
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned long long int), 16);
	else if (params->len >= 4)
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned long int), 16);
	else if (params->len >= 2)
		temp = ft_itoa_base_unsign((unsigned short)va_arg(ap, uintmax_t), 16);
	else if (params->len >= 1)
		temp = ft_itoa_base_unsign((unsigned char)va_arg(ap, uintmax_t), 16);
	else
		temp = ft_itoa_base_unsign(va_arg(ap, unsigned int), 16);
	i = -1;
	if (params->conv == 'X')
		while (temp[++i])
			temp[i] = ft_toupper(temp[i]);
	return (temp);
}
