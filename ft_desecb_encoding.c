/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desecb_encoding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 14:09:35 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/20 14:09:36 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

uint64_t		ft_input_to_bits(char *str)
{
	uint64_t		res;
	int				i;

	res = 0;
	i = -1;
	while (++i < 8)
	{
		res <<= 8;
		res = res | *(str + i);
	}
	return (res);
}

uint64_t		ft_des_permut(uint64_t nb, uint8_t prm[], int new_sz, int curr_sz)
{
	int			i;
	uint64_t	res;

	i = -1;
	res = 0;
	while (++i < new_sz)
	{
		res <<= 1;
		res = res | ((nb >> (curr_sz - prm[i])) & 1);
	}
	return (res);
}

char			*ft_des_encode_block(char *input, uint64_t key)
{
	uint64_t	converted;
	int			i;
	uint64_t	left;
	uint64_t	left_new;
	uint64_t	right;

	i = -1;
	converted = ft_input_to_bits(input);
	converted = ft_des_permut(converted, g_initial_shuffle, 64, 64);
	key = ft_des_permut(key, g_pc1, 56, 64);
	while (++i < 16)
	{
		left = L32OF64(converted);
		left_new = R32OF64(converted);
		right = R32OF64(converted);
		right = ft_des_permut(right, g_expand_right, 48, 32);
		key = ft_shuffle_key(key, g_key_shift[i]);
		right ^= ft_des_permut(key, g_pc2, 48, 56);
		right = ft_s_boxes(right);
		right = ft_des_permut(right, g_p_permut, 32, 32);
		right ^= left;
		converted = JOINBITS(left_new, right, 32);
	}
	converted = (R32OF64(converted) << 32) | (L32OF64(converted));
	return (ft_string_from_bits(ft_des_permut(converted, g_finish, 64, 64)));
}

char			*ft_desecb_encode_all(char *input, char *key, t_ssl_cmds *cmds)
{
	char		*res;
	char		*temp;
	char		*fordel;
	char		*for_work;
	uint64_t	bit_key;

	res = ft_strnew(0);
	cmds->len_to_code = ft_strlen(input);
	bit_key = ft_key_to_bits(key);
	while (cmds->len_coded <= cmds->len_to_code)
	{
		for_work = ft_filled_by_len(input);
		temp = ft_des_encode_block(for_work, bit_key);
		fordel = res;
		res = ft_des_join_block(res, temp, cmds);
		ft_strdel(&temp);
		ft_strdel(&for_work);
		ft_strdel(&fordel);
		// ft_printf("sz of res = %zu\n", ft_strlen(res));
		cmds->len_coded += 8;
		input += 8;
		cmds->size_output +=8;
	}
	return (res);
}

char		*ft_desecb_encode(int ac, char **av, t_ssl_cmds *cmds)
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
		return (NULL);
	}
	for_work = ft_get_str(ac, av, cmds);
	if (!for_work)
		return (NULL);
	res = ft_desecb_encode_all(for_work, key, cmds);
	ft_strdel(&for_work);
	return (res);
}
