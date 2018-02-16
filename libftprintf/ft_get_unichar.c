/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unichar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:40:03 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/25 12:40:04 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <locale.h>

static char	*ft_unichar_1byte(unsigned int nb)
{
	char	*res;

	res = ft_strnew(1);
	res[0] = nb;
	return (res);
}

static char	*ft_unichar_2bytes(unsigned int nb)
{
	char	*res;

	res = ft_strnew(2);
	res[0] = 192 | (nb >> 6);
	res[1] = 128 | (nb & 63);
	return (res);
}

static char	*ft_unichar_3bytes(unsigned int nb)
{
	char	*res;

	res = ft_strnew(3);
	res[0] = 224 | (nb >> 12);
	res[1] = 128 | ((nb >> 6) & 63);
	res[2] = 128 | (nb & 63);
	return (res);
}

static char	*ft_unichar_4bytes(unsigned int nb)
{
	char	*res;

	res = ft_strnew(4);
	res[0] = 240 | (nb >> 18);
	res[1] = 128 | ((nb >> 12) & 63);
	res[2] = 128 | ((nb >> 6) & 63);
	res[3] = 128 | (nb & 63);
	return (res);
}

char		*ft_get_unichar(unsigned int uni)
{
	int				len;
	unsigned int	cp_uni;
	char			*res;

	if (uni == 0 && (res = ft_strnew(1)) != NULL)
	{
		*res = -100;
		return (res);
	}
	len = 0;
	cp_uni = uni;
	while (cp_uni)
	{
		cp_uni >>= 1;
		len++;
	}
	if (len >= 0 && len <= 7)
		res = ft_unichar_1byte(uni);
	if (len >= 8 && len <= 11)
		res = ft_unichar_2bytes(uni);
	else if (len >= 12 && len <= 16)
		res = ft_unichar_3bytes(uni);
	else if (len >= 17 && len <= 21)
		res = ft_unichar_4bytes(uni);
	return (res);
}
