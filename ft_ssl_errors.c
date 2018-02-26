/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 12:03:52 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/16 12:03:54 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

int		ft_print_usage(void)
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (1);
}

int		ft_ssl_error(char *cmd, t_ssl_cmds **cmds)
{
	ft_printf("ft_ssl: Error '%s' is an invalid command.\n", cmd);
	ft_printf("\nStandart commands:\n");
	ft_printf("\nMessage Digest commands:\n");
	ft_printf("\nCipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc\n");
	free(*cmds);
	*cmds = NULL;
	return (1);
}
