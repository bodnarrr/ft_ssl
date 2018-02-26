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

static char		*ft_desecb_decode_block(char *in, uint64_t key, t_ssl_cmds *cmd)
{
	uint64_t	conv;
	int			i;
	uint64_t	left;
	uint64_t	left_new;
	uint64_t	right;

	i = -1;
	conv = ft_input_to_bits(in);
	conv = ft_des_permut(conv, g_initial_shuffle, 64, 64);
	key = ft_des_permut(key, g_pc1, 56, 64);
	key = ft_shuffle_key(key, 1);
	while (++i < 16)
	{
		left = L32OF64(conv);
		left_new = R32OF64(conv);
		right = R32OF64(conv);
		right = ft_des_permut(right, g_expand_right, 48, 32);
		key = ft_shuffle_key_rev(key, g_key_shift[i]);
		right ^= ft_des_permut(key, g_pc2, 48, 56);
		right = ft_des_permut(ft_s_boxes(right), g_p_permut, 32, 32);
		right ^= left;
		conv = JOINBITS(left_new, right, 32);
	}
	conv = (R32OF64(conv) << 32) | (L32OF64(conv));
	return (ft_string_from_bits_r(ft_des_permut(conv, g_finish, 64, 64), cmd));
}

void			ft_clear_some_mem(t_ssl_cmds *cmds, char **temp, char **fordel,
				char **input)
{
	ft_strdel(temp);
	ft_strdel(fordel);
	cmds->size_output += cmds->curr_block;
	*input += 8;
	cmds->len_coded += 8;
}

static char		*ft_desecb_decode_all(char *input, char *key, t_ssl_cmds *cmds)
{
	char		*res;
	char		*temp;
	char		*fordel;
	uint64_t	bit_key;

	res = ft_strnew(0);
	bit_key = ft_key_to_bits(key);
	while (cmds->len_coded < cmds->len_to_code)
	{
		if (cmds->len_to_code - cmds->len_coded == 8)
			cmds->last_iter = 1;
		temp = ft_desecb_decode_block(input, bit_key, cmds);
		if (cmds->last_iter)
			temp = ft_des_clear_last_block(&temp, cmds);
		if (temp == NULL)
		{
			ft_strdel(&res);
			return (NULL);
		}
		fordel = res;
		res = ft_ssl_join_block(res, temp, cmds->size_output, cmds->curr_block);
		ft_clear_some_mem(cmds, &temp, &fordel, &input);
	}
	return (res);
}

static char		*ft_base_for_ecb(char **for_work, t_ssl_cmds *cmds)
{
	char		*res;

	res = ft_base64_decode_all(*for_work, cmds);
	ft_strdel(for_work);
	cmds->len_coded = 0;
	cmds->len_to_code = cmds->size_output;
	cmds->size_output = 0;
	return (res);
}

char			*ft_desecb_decode(int ac, char **av, t_ssl_cmds *cmds)
{
	char		*res;
	char		*for_work;
	char		*key;

	if (cmds->key)
		key = ft_strdup(av[cmds->keypos]);
	else
		key = getpass("Enter 64-bit key in HEX: ");
	if (!ft_des_check_key(key, "0") && ft_printf("Key is incorrect!\n"))
		return (NULL);
	for_work = ft_get_str(ac, av, cmds);
	if (!for_work)
		return (NULL);
	if (cmds->base64)
		for_work = ft_base_for_ecb(&for_work, cmds);
	if (cmds->len_to_code % 8 != 0 && ft_printf("Incorrect input!\n"))
	{
		ft_strdel(&for_work);
		return (NULL);
	}
	res = ft_desecb_decode_all(for_work, key, cmds);
	ft_strdel(&for_work);
	return (res);
}
