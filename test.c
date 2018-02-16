/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:26:09 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/16 15:26:13 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

int		main(int ac, char **av)
{
	char	buf[9];
	int		ret;
	int		i;

	if (ac == 0)
		return (1);
	i = 0;
	if (ft_strequ(av[1], "-in") == 1)
		while ((ret = read(0, buf, 8)) > 0)
		{
			buf[ret] = '\0';
			ft_printf("buf[%d] = %s\n", i, buf);
			i++;
		}
}
