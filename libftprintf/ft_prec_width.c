/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 09:44:39 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/30 09:44:42 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_apply_precision(char **temp, t_params *params)
{
	char	*zrs;
	char	*fordel;

	if (params->dot && params->conv != 'c' && params->conv != 's'
		&& params->conv != '%' && params->conv != 'S')
		params->f_zero = 0;
	if (ft_strchr("idDoOuUxXpSb", params->conv) && params->dot)
	{
		if (**temp != '-')
			ft_prec_for_positive(temp, params);
		if (params->dot && **temp == '-'
			&& params->prec > (int)ft_strlen(*temp) - 1)
			ft_prec_for_negative(temp, params);
	}
	else if (params->conv == 's' && params->dot &&
		params->prec < (int)ft_strlen(*temp))
	{
		zrs = ft_strnew(params->prec);
		zrs = ft_memcpy(zrs, *temp, params->prec);
		fordel = *temp;
		*temp = ft_strdup(zrs);
		ft_strdel(&zrs);
		ft_strdel(&fordel);
	}
}

void		ft_apply_width(char **temp, t_params *params)
{
	char	*spc;
	char	*fordel;
	int		wd;

	if (ft_strchr("idDoOuUxXpSscb%", params->conv)
		&& params->width > (int)ft_strlen(*temp))
	{
		wd = params->width - (int)ft_strlen(*temp);
		if (params->f_sharp && params->f_zero)
			wd -= 2;
		spc = ft_strnew(wd);
		spc = ft_memset(spc, ' ', wd);
		fordel = *temp;
		if (params->f_min)
			*temp = ft_strjoin(*temp, spc);
		else
			*temp = ft_strjoin(spc, *temp);
		ft_strdel(&spc);
		ft_strdel(&fordel);
	}
}
