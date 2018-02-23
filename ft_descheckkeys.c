/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_descheckkeys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 18:26:21 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/20 18:26:22 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

int				ft_des_check_key(char *key)
{
	int			i;
	const char	hex[22] = "0123456789ABCDEFabcdef";

	if (ft_strlen(key) > 16)
		return (0);
	i = 0;
	while (key[i])
	{
		if (!ft_strchr(hex, key[i]))
			return (0);
		i++;
	}
	return (1);
}
