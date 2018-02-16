/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:30:08 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/29 17:30:09 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_apply_flags(char **temp, t_params *params)
{
	ft_apply_precision(temp, params);
	if (params->f_sharp)
		ft_apply_sharp(temp, params);
	ft_apply_space(temp, params);
	if (params->f_plus)
		ft_apply_plus(temp, params);
	ft_apply_width(temp, params);
	ft_apply_zero(temp, params);
}
