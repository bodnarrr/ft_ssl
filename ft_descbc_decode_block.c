/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_descbc_decode_block.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:53:25 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/26 18:53:26 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

char			*ft_descbc_decode_block(char *in, uint64_t key, uint64_t vect,
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
