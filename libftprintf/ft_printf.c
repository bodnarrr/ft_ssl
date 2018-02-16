/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 09:44:56 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/30 09:44:58 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*ft_replace_zeros(char *str)
{
	int			i;
	char		*res;

	i = 0;
	res = ft_strdup(str);
	while (*(res + i))
	{
		if (*(res + i) == -100)
			*(res + i) = 0;
		i++;
	}
	return (res);
}

static char		*ft_take_clear(char **format, char **buff)
{
	size_t		i;
	char		*temp1;
	char		*temp2;

	i = 0;
	while (*(*format + i) != '%' && *(*format + i))
		i++;
	temp1 = (char*)malloc(sizeof(char) * (i + 1));
	temp1 = ft_memcpy(temp1, *format, i);
	temp1[i] = '\0';
	temp2 = *buff;
	*buff = ft_strjoin(*buff, temp1);
	ft_strdel(&temp1);
	ft_strdel(&temp2);
	*format += i;
	return (*buff);
}

static char		*ft_take_current_arg(char **buff, t_params *params, va_list ap)
{
	char		*temp;
	char		*fordel;

	if (params->conv == 0)
		temp = ft_strnew(0);
	else if (ft_strchr("idDoOxXuUp", params->conv))
		temp = ft_typical_arg(params, ap);
	else if (params->conv == 'C' || (params->conv == 'c' && params->len >= 4
		&& params->len < 8) || params->conv == 'S'
		|| (params->conv == 's' && params->len >= 4))
		temp = ft_unicode_arg(params, ap);
	else if (params->conv == 'c' || params->conv == 's' || params->conv == '%')
		temp = ft_get_char_str_perc(&temp, params->conv, ap);
	else if (params->conv == 'b')
		temp = ft_get_binary(ap);
	ft_apply_flags(&temp, params);
	fordel = *buff;
	*buff = ft_strjoin(*buff, temp);
	ft_strdel(&fordel);
	ft_strdel(&temp);
	return (*buff);
}

int				ft_print(va_list ap, char *format)
{
	char		*buff;
	t_params	params;
	char		*res;
	int			ret;

	if (!format)
		return (-1);
	buff = ft_strnew(0);
	while (*format)
	{
		ft_bzero(&params, sizeof(t_params));
		params.prec = -1;
		params.width = -1;
		buff = ft_take_clear(&format, &buff);
		if (*format && *format++ == '%')
			ft_parse_printf(&format, &params, ap);
		buff = params.conv ? ft_take_current_arg(&buff, &params, ap) : buff;
	}
	res = ft_replace_zeros(buff);
	ret = (int)write(1, res, ft_strlen(buff));
	ft_strdel(&buff);
	ft_strdel(&res);
	return (ret);
}

int				ft_printf(char *format, ...)
{
	va_list	ap;
	int		res;

	if (format == NULL)
		return (0);
	va_start(ap, format);
	res = ft_print(ap, format);
	va_end(ap);
	return (res);
}
