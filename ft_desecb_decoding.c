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

char			*ft_string_from_bits_r(uint64_t inf, t_ssl_cmds *cmds)
{
	char		*res;
	int			size;
	uint8_t		temp;
	int			i;

	size = 8;
	if ((inf & 255) > 1 && (inf & 255) < 9)
		size = 8 - (inf & 255);
	if (size == 0)
		return (ft_strdup("\0"));
	cmds->size_output += size;
	res = ft_strnew(size);
	i = -1;
	while (++i < size)
	{
		temp = (inf >> (56 - i * 8)) & 255;
		res[i] = temp;
	}
	return (res);
}

static uint64_t	ft_shuffle_key_rev(uint64_t key, uint8_t i)
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

char			*ft_desecb_decode_block(char *in, uint64_t key, t_ssl_cmds *cmd)
{
	uint64_t	conv;
	int			i;
	uint64_t	left;
	uint64_t	left_new;
	uint64_t	right;

	i = -1;
	conv = ft_input_to_bits(in);
	conv = 0x85E813540F0AB405;
	conv = ft_des_permut(conv, g_initial_shuffle, 64, 64);
	key = 0x133457799BBCDFF1;
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
	ft_printf("res = %.64b\n", ft_des_permut(conv, g_finish, 64, 64));
	return (ft_string_from_bits_r(ft_des_permut(conv, g_finish, 64, 64), cmd));
}

char			*ft_desecb_decode_all(char *input, char *key, t_ssl_cmds *cmds)
{
	char		*res;
	char		*temp;
	char		*fordel;
	uint64_t	bit_key;

	res = ft_strnew(0);
	bit_key = ft_key_to_bits(key);
	while (*input)
	{
		temp = ft_desecb_decode_block(input, bit_key, cmds);
		fordel = res;
		res = ft_strjoin(res, temp);
		ft_strdel(&temp);
		ft_strdel(&fordel);
		input += 8;
	}
	return (res);
}

static int		ft_desecb_check_input(char *input)
{
	size_t		len;

	len = ft_strlen(input);
	if (len % 8 != 0)
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
	{
		ft_strdel(&key);
		return (NULL);
	}
	for_work = ft_get_str(ac, av, cmds);
	if (!for_work)
		return (NULL);
	if (!ft_desecb_check_input(for_work) && ft_printf("Incorrect input!\n"))
	{
		ft_strdel(&for_work);
		return (NULL);
	}
	res = ft_desecb_decode_all(for_work, key, cmds);
	ft_strdel(&for_work);
	return (res);
}
