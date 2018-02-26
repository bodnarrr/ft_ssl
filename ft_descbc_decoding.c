/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_descbc_decoding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 13:55:16 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/26 13:55:17 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

static char		*ft_descbc_decode_block(char *in, uint64_t key, uint64_t vect,
				t_ssl_cmds *cmd)
{
	uint64_t	conv;
	int			i;
	uint64_t	left;
	uint64_t	left_new;
	uint64_t	right;

	i = -1;
	conv = ft_input_to_bits(in);
	cmd->vect_new = conv;
	conv = ft_des_permut(conv, g_initial_shuffle, 64, 64);
	key = ft_des_permut(key, g_pc1, 56, 64);
	key = ft_shuffle_key(key, 1);
	while (++i < 16)
	{
		left = L32OF64(conv);
		left_new = R32OF64(conv);
		right = ft_des_permut(R32OF64(conv), g_expand_right, 48, 32);
		key = ft_shuffle_key_rev(key, g_key_shift[i]);
		right = right ^ ft_des_permut(key, g_pc2, 48, 56);
		right = ft_des_permut(ft_s_boxes(right), g_p_permut, 32, 32);
		conv = JOINBITS(left_new, right ^ left, 32);
	}
	conv = (R32OF64(conv) << 32) | (L32OF64(conv));
	return (ft_string_from_bits_r(ft_des_permut(conv, g_finish, 64, 64) ^ vect,
		cmd));
}

static char		*ft_descbc_decode_all(char *input, char *key, char *iv,
				t_ssl_cmds *cmds)
{
	char		*res;
	char		*temp;
	char		*fordel;
	uint64_t	bit_key;
	uint64_t	bit_vector;

	res = ft_strnew(0);
	bit_key = ft_key_to_bits(key);
	bit_vector = ft_key_to_bits(iv);
	while (cmds->len_coded < cmds->len_to_code)
	{
		if (cmds->len_to_code - cmds->len_coded == 8)
			cmds->last_iter = 1;
		if (cmds->len_coded == 0)
			temp = ft_descbc_decode_block(input, bit_key, bit_vector, cmds);
		else
			temp = ft_descbc_decode_block(input, bit_key, cmds->vect_new, cmds);
		if (cmds->last_iter)
			temp = ft_des_clear_last_block(&temp, cmds);
		if (temp == NULL)
		{
			ft_strdel(&res);
			return (NULL);
		}
		cmds->vector = ft_descbc_make_vector(temp);
		fordel = res;
		res = ft_ssl_join_block(res, temp, cmds->size_output, cmds->curr_block);
		ft_strdel(&temp);
		ft_strdel(&fordel);
		cmds->size_output += cmds->curr_block;
		input += 8;
		cmds->len_coded += 8;
	}
	return (res);
}

char			*ft_descbc_decode(int ac, char **av, t_ssl_cmds *cmds)
{
	char		*res;
	char		*for_work;
	char		*key;
	char		*iv;

	if (cmds->key && av[cmds->keypos])
		key = ft_strdup(av[cmds->keypos]);
	else
		key = getpass("Enter 64-bit key in HEX: ");
	if (cmds->iv && av[cmds->ivpos])
		iv = ft_strdup(av[cmds->ivpos]);
	else
		iv = getpass("Enter 64-bit vector in HEX: ");
	if (!ft_des_check_key(key) && ft_printf("Key is incorrect!\n"))
		return (NULL);
	if (!ft_des_check_key(iv) && ft_printf("Vector is incorrect!\n"))
		return (NULL);
	for_work = ft_get_str(ac, av, cmds);
	if (!for_work)
		return (NULL);
	if (cmds->len_to_code % 8 != 0 && ft_printf("Incorrect input!\n"))
	{
		ft_strdel(&for_work);
		return (NULL);
	}
	res = ft_descbc_decode_all(for_work, key, iv, cmds);
	ft_strdel(&for_work);
	return (res);
}
