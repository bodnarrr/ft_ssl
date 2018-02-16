/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zero_nonprt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:54:00 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/29 16:54:11 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_zero_nonptr(char **str, t_params *params, int i)
{
	int j;

	if (*(*str + i) == '-' || *(*str + i) == '+')
	{
		j = 1;
		**str = *(*str + i);
		while (!ft_isalnum(*(*str + j)))
		{
			*(*str + j) = '0';
			j++;
		}
	}
	else
	{
		while (i && *(*str + i - 1) == ' ')
		{
			if (params->f_space && i == 1)
				break ;
			*(*str + i - 1) = '0';
			i--;
		}
	}
}
