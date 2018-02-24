/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_descbc_encoding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:50:32 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/24 16:50:33 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

char			*ft_descbc_encode_block(char *input, uint64_t key, uint64_t iv)
{
	uint64_t	conv;
	int			i;
	uint64_t	left;
	uint64_t	left_new;
	uint64_t	right;

	i = -1;
	conv = ft_input_to_bits(input);
	conv ^= iv;
	conv = ft_des_permut(conv, g_initial_shuffle, 64, 64);
	key = ft_des_permut(key, g_pc1, 56, 64);
	while (++i < 16)
	{
		left = L32OF64(conv);
		left_new = R32OF64(conv);
		right = R32OF64(conv);
		right = ft_des_permut(right, g_expand_right, 48, 32);
		key = ft_shuffle_key(key, g_key_shift[i]);
		right ^= ft_des_permut(key, g_pc2, 48, 56);
		right = ft_des_permut(ft_s_boxes(right), g_p_permut, 32, 32);
		right ^= left;
		conv = JOINBITS(left_new, right, 32);
	}
	conv = (R32OF64(conv) << 32) | (L32OF64(conv));
	return (ft_string_from_bits(ft_des_permut(conv, g_finish, 64, 64)));
}

char			*ft_descbc_encode_all(char *input, char *key, char *iv,
				t_ssl_cmds *cmds)
{
	char		*res;
	char		*temp;
	char		*fordel;
	char		*for_work;
	uint64_t	bit_key;

	res = ft_strnew(0);
	bit_key = ft_key_to_bits(key);
	while (cmds->len_coded <= cmds->len_to_code)
	{
		for_work = ft_filled_by_len(input);
		temp = ft_descbc_encode_block(for_work, bit_key, ft_key_to_bits(iv));
		fordel = res;
		res = ft_ssl_join_block(res, temp, cmds->len_coded, 8);
		ft_strdel(&temp);
		ft_strdel(&for_work);
		ft_strdel(&fordel);
		cmds->len_coded += 8;
		input += 8;
		cmds->size_output += 8;
	}
	return (res);
}

char			*ft_descbc_encode(int ac, char **av, t_ssl_cmds *cmds)
{
	char		*res;
	char		*for_work;
	char		*key;
	char		*iv;

	if (cmds->key)
		key = ft_strdup(av[cmds->keypos]);
	else
		key = getpass("Enter 64-bit key in HEX: ");
	if (cmds->iv)
		iv = ft_strdup(av[cmds->ivpos]);
	else
		iv = getpass("Enter 64-bit vector in HEX: ");
	if (!ft_des_check_key(key))
	{
		ft_strdel(&key);
		ft_strdel(&iv);
		ft_printf("Key is incorrect!\n");
		return (NULL);
	}
	if (!ft_des_check_key(iv))
	{
		ft_strdel(&key);
		ft_strdel(&iv);
		ft_printf("Vector is incorrect!\n");
		return (NULL);
	}
	for_work = ft_get_str(ac, av, cmds);
	if (!for_work)
		return (NULL);
	res = ft_descbc_encode_all(for_work, key, iv, cmds);
	ft_strdel(&for_work);
	return (res);
}
