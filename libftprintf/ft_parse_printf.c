/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 09:44:00 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/30 09:44:04 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*ft_parse_lenght(char **s, t_params *params)
{
	while (**s && (**s == 'h' || **s == 'l' || **s == 'L' || **s == 'z'
			|| **s == 'j' || **s == 't'))
	{
		if (**s == 'h' && *(*s - 1) != 'h')
			params->len = params->len | 2;
		if (**s == 'h' && *(*s - 1) == 'h')
		{
			params->len = params->len & 4294967293;
			params->len = params->len | 1;
		}
		if (**s == 'l' && *(*s - 1) != 'l')
			params->len = params->len | 4;
		if (**s == 'l' && *(*s - 1) == 'l')
			params->len = params->len | 8;
		if (**s == 'z')
			params->len = params->len | 16;
		if (**s == 'j')
			params->len = params->len | 32;
		(*s)++;
	}
	return (*s);
}

static char	*ft_parse_precision(char **s, t_params *params, va_list ap)
{
	(*s)++;
	params->dot = '+';
	if (**s == '*')
	{
		params->prec = va_arg(ap, int);
		if (params->prec < 0)
		{
			params->prec = -1;
			params->dot = 0;
		}
		(*s)++;
	}
	else
	{
		params->prec = ft_atoi(*s);
		while (**s && **s >= '0' && **s <= '9')
			(*s)++;
	}
	return (*s);
}

static char	*ft_parse_width(char **s, t_params *params, va_list ap)
{
	if (**s == '*')
	{
		params->width = va_arg(ap, int);
		(*s)++;
		if (params->width < 0)
		{
			params->width *= -1;
			params->f_min = '+';
		}
	}
	else
	{
		params->width = ft_atoi(*s);
		while (**s && **s >= '0' && **s <= '9')
			(*s)++;
	}
	return (*s);
}

static char	*ft_parse_flags(char **s, t_params *params)
{
	while (**s && (**s == ' ' || **s == '#' || **s == '+' || **s == '-'
		|| **s == '0'))
	{
		if (**s == ' ')
			params->f_space = '+';
		if (**s == '#')
			params->f_sharp = '+';
		if (**s == '+')
		{
			params->f_plus = '+';
			params->f_space = 0;
		}
		if (**s == '0')
			params->f_zero = '+';
		if (**s == '-')
		{
			params->f_min = '+';
			params->f_zero = 0;
		}
		(*s)++;
	}
	return (*s);
}

void		ft_parse_printf(char **s, t_params *params, va_list ap)
{
	if (s == NULL)
		return ;
	while (**s)
	{
		if (**s == ' ' || **s == '#' || **s == '+' || **s == '-' || **s == '0')
			*s = ft_parse_flags(s, params);
		if ((**s >= '1' && **s <= '9') || **s == '*')
			*s = ft_parse_width(s, params, ap);
		if (**s == '.')
			*s = ft_parse_precision(s, params, ap);
		if (**s == 'h' || **s == 'l' || **s == 'L' || **s == 'z'
			|| **s == 'j' || **s == 't')
			*s = ft_parse_lenght(s, params);
		if (ft_strchr("isixpdoOuUDXcSCb%", **s))
		{
			params->conv = **s;
			(*s)++;
			break ;
		}
		else
		{
			ft_bzero(params, sizeof(t_params));
			break ;
		}
	}
}
