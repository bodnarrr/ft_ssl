/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec_for_positive.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 19:53:41 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/29 19:53:50 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_prec_for_negative(char **temp, t_params *params)
{
	char	*zrs;
	char	*fordel;
	int		adding;

	adding = params->prec - ft_strlen(*temp) + 1;
	zrs = ft_strnew(adding);
	zrs = ft_memset(zrs, '0', adding);
	fordel = *temp;
	*temp = ft_strjoin(zrs, *temp + 1);
	ft_strdel(&zrs);
	ft_strdel(&fordel);
	fordel = *temp;
	*temp = ft_strjoin("-", *temp);
	ft_strdel(&fordel);
}

void		ft_prec_for_positive(char **temp, t_params *params)
{
	char	*zrs;
	char	*fordel;
	int		adding;

	if (params->prec > (int)ft_strlen(*temp))
	{
		adding = params->prec - ft_strlen(*temp);
		if ((params->conv == 'o' || params->conv == 'O') && params->f_sharp)
			adding--;
		zrs = ft_strnew(adding);
		zrs = ft_memset(zrs, '0', adding);
		fordel = *temp;
		*temp = ft_strjoin(zrs, *temp);
		ft_strdel(&zrs);
		ft_strdel(&fordel);
	}
	if ((params->prec == 0 && params->conv != 'p' && !ft_strcmp(*temp, "0"))
		|| (params->prec == 0 && params->conv == 'S'))
	{
		fordel = *temp;
		*temp = ft_strdup("");
		ft_strdel(&fordel);
	}
}
