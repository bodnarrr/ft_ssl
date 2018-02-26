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

char			*ft_des_clear_last_block(char **block, t_ssl_cmds *cmds)
{
	int			new_size;
	char		*ret;

	if ((*block)[7] > 8 || (*block)[7] < 1)
	{
		ft_strdel(block);
		return (NULL);
	}
	new_size = 8 - (*block)[7];
	cmds->curr_block = new_size;
	ret = ft_strsub(*block, 0, new_size);
	ft_strdel(block);
	return (ret);
}

char			*ft_string_from_bits_r(uint64_t inf, t_ssl_cmds *cmds)
{
	char		*res;
	uint8_t		temp;
	int			i;

	res = ft_strnew(8);
	i = -1;
	while (++i < 8)
	{
		temp = (inf >> (56 - i * 8)) & 255;
		res[i] = temp;
	}
	cmds->curr_block = 8;
	return (res);
}

uint64_t		ft_shuffle_key_rev(uint64_t key, uint8_t i)
{
	uint64_t	res;
	uint64_t	left;
	uint64_t	right;
	int			clear;

	res = 0;
	if (i == 1)
		clear = 1;
	else if (i == 2)
		clear = 3;
	left = L28OF56(key);
	right = R28OF56(key);
	left = (left >> i) | ((left & clear) << (28 - i));
	right = (right >> i) | ((right & clear) << (28 - i));
	return (JOINBITS(left, right, 28));
}

static char		*ft_desecb_decode_block(char *in, uint64_t key, t_ssl_cmds *cmd)
{
	uint64_t	conv;
	int			i;
	uint64_t	left;
	uint64_t	left_new;
	uint64_t	right;

	i = -1;
	conv = ft_input_to_bits(in);
	// ft_printf("conv = %.16llX\n", conv);
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
	// ft_printf("res = %.16llX\n", ft_des_permut(conv, g_finish, 64, 64));
	return (ft_string_from_bits_r(ft_des_permut(conv, g_finish, 64, 64), cmd));
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
		ft_strdel(&temp);
		ft_strdel(&fordel);
		cmds->size_output += cmds->curr_block;
		input += 8;
		cmds->len_coded += 8;
	}
	return (res);
}

int				ft_des_check_input(t_ssl_cmds *cmds)
{
	if (cmds->len_to_code % 8 != 0)
		return (0);
	return (1);
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
	if (!ft_des_check_key(key) && ft_printf("Key is incorrect!\n"))
		return (NULL);
	for_work = ft_get_str(ac, av, cmds);
	if (!for_work)
		return (NULL);
	if (!ft_des_check_input(cmds) && ft_printf("Incorrect input!\n"))
	{
		ft_strdel(&for_work);
		return (NULL);
	}
	res = ft_desecb_decode_all(for_work, key, cmds);
	ft_strdel(&for_work);
	return (res);
}
