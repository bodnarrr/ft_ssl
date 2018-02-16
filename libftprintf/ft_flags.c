/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:12:30 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/18 13:12:32 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_apply_sharp(char **str, t_params *params)
{
	int		i;

	if (**str == '\0' && !params->f_sharp)
		return ;
	if (params->f_zero)
	{
		ft_apply_width(str, params);
		i = 0;
		while (**str && *(*str + i) && *(*str + i) == ' ')
		{
			*(*str + i) = '0';
			i++;
		}
	}
	if (params->conv == 'x' || params->conv == 'X' || params->conv == 'o'
		|| params->conv == 'O')
		ft_sharp_octal_hexa(str, params);
}

void		ft_apply_space(char **str, t_params *params)
{
	char	*fordel;

	if ((params->conv == 'i' || params->conv == 'd' || params->conv == 'D')
		&& params->f_space && **str && **str != '-' && !params->f_plus)
	{
		fordel = *str;
		*str = ft_strjoin(" ", *str);
		ft_strdel(&fordel);
	}
}

void		ft_apply_plus(char **str, t_params *params)
{
	char	*fordel;

	if ((params->conv == 'i' || params->conv == 'd' || params->conv == 'D')
		&& **str && **str != '-')
	{
		fordel = *str;
		*str = ft_strjoin("+", *str);
		ft_strdel(&fordel);
	}
}

void		ft_apply_zero(char **str, t_params *params)
{
	int		i;
	char	*cpy;
	char	*temp;
	char	*fordel;

	cpy = *str;
	i = 0;
	while (*cpy && *cpy == ' ')
	{
		i++;
		cpy++;
	}
	if (params->f_zero && params->conv == 'p'
		&& !ft_strcmp(cpy, "0x0"))
	{
		temp = ft_strnew(i);
		temp = ft_memset(temp, '0', i);
		fordel = *str;
		*str = ft_strjoin("0x0", temp);
		ft_strdel(&temp);
		ft_strdel(&fordel);
	}
	else if (params->f_zero && ((params->dot && params->prec != -1)
		|| params->width != -1) && !params->f_min)
		ft_zero_nonptr(str, params, i);
}
