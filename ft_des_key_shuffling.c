/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_key_shuffling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:55:43 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/26 17:55:44 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

uint64_t		ft_shuffle_key(uint64_t key, uint8_t i)
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
	left = (left << i & 0xFFFFFFF) | (left >> (28 - i) & clear);
	right = (right << i & 0xFFFFFFF) | (right >> (28 - i) & clear);
	return (JOINBITS(left, right, 28));
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
