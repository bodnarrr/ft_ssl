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

int				ft_des_check_key(char *key, char *iv)
{
	int			i;
	const char	hex[22] = "0123456789ABCDEFabcdef";

	if (ft_strlen(key) > 16 && ft_printf("Key is incorrect!\n"))
		return (0);
	i = -1;
	while (key[++i])
		if (!ft_strchr(hex, key[i]) && ft_printf("Key is incorrect!\n"))
			return (0);
	if (ft_strlen(iv) > 16 && ft_printf("Vector is incorrect!\n"))
		return (0);
	i = -1;
	while (iv[++i])
		if (!ft_strchr(hex, iv[i]) && ft_printf("Vector is incorrect!\n"))
			return (0);
	return (1);
}
