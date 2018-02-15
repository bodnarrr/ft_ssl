/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 20:26:47 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/12 20:26:48 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H

# define CENTR4OF6(x)		((x) >> 1 & 15)
# define FL2OF6(x) 			((x & 1) | (x >> 4 & 2))
# define L32OF64(x)			((x) >> 32)
# define R32OF64(x)			((x) & 0xFFFFFFFF)
# define L28OF56(x)			((x) >> 28)
# define R28OF56(x)			((x) & 0xFFFFFFF)
# define JOINBITS(x, y, sz)	((x << sz) | y)
# define EIGHTED 			"\b\b\b\b\b\b\b\b"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include <inttypes.h>
# include "libftprintf.h"

typedef struct	s_desecb
{
	size_t		input_len;
	size_t		encryted;
	uint64_t	key;
	uint64_t	vector;
}				t_des;
#endif
