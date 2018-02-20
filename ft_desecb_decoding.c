/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desecb_decoding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 19:39:34 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/20 19:39:35 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

char		*ft_desecb_decode_all(char *input, char *key, t_ssl_cmds *cmds)
{
	char		*res;
	char		*temp;
	char		*fordel;
	uint64_t	bit_key;

	res = ft_strnew(0);
	bit_key = ft_key_to_bits(key);
	while (*input)
	{
		temp = ft_des_decode_block(input, bit_key);
	}

}

int			ft_desecb_decode(int ac, char **av, t_ssl_cmds *cmds)
{
	char	*res;
	char	*for_work;
	char	*key;

	if (cmds->key)
		key = ft_strdup(av[cmds->keypos]);
	else
		key = getpass("Enter 64-bit key in HEX: ");
	if (!ft_des_check_key(key))
	{
		ft_strdel(&key);
		ft_printf("Key is incorrect!\n");
		return (1);
	}
	for_work = ft_get_str(ac, av, cmds);
	if (!for_work)
		return (1);
	if (ft_strlen(for_work) % 8 != 0 && ft_printf("Incorrect input!\n"))
		return (1);
	res = ft_desecb_decode_all(for_work, key, cmds);
	ft_strdel(&for_work);
	ft_ssl_write(av, &res, cmds);
	return (0);
}
