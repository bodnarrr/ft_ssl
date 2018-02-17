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
# define RDBS64				3
# define RDDES				8

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdbool.h>
# include "libftprintf/libftprintf.h"

typedef struct	s_desecb
{
	size_t		input_len;
	size_t		encryted;
	uint64_t	key;
	uint64_t	vector;
}				t_des;

typedef struct	s_ssl_cmds
{
	uint		mode;
	bool		encr;
	bool		decr;
	bool		in;
	uint		inpos;
	bool		out;
	uint		outpos;
	bool		key;
	uint 		keypos;
	bool		base64;
	int			ret;
	uint		sz_bs64;
	
}				t_ssl_cmds;

int				ft_print_usage(void);
int				ft_ssl_error(char *cmd, t_ssl_cmds **cmds);
t_ssl_cmds		*ft_ssl_get_commands(int ac, char **av);
int				ft_base64(int ac, char **av, t_ssl_cmds *cmds);

#endif
