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
# define BS64EN				3
# define BS64DE				4
# define RDDES				8
# define BUFF_SSL			64

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
	uint		keypos;
	bool		iv;
	uint		ivpos;
	uint64_t	vector;
	uint64_t	vect_new;
	bool		base64;
	int			ret;
	int			size_output;
	uint		len_to_code;
	uint		len_coded;
	bool		last_iter;
	uint		curr_block;

}				t_ssl_cmds;

int				ft_print_usage(void);
int				ft_ssl_error(char *cmd, t_ssl_cmds **cmds);
t_ssl_cmds		*ft_ssl_get_commands(int ac, char **av);

int				ft_base64(char **av, t_ssl_cmds *cmds);
char			*ft_base64_encode_all(char *for_work, t_ssl_cmds *cmds);
void			ft_ssl_write(char **av, char **str, t_ssl_cmds *cmds);
char			*ft_base64_decode_all(char *for_work, t_ssl_cmds *cmds);
int				ft_base64_check_input(char *str);

char			*ft_get_str(char **av, t_ssl_cmds *cmds);

int				ft_desecb(char **av, t_ssl_cmds *cmds);
int				ft_des_check_input(t_ssl_cmds *cmds);
char			*ft_desecb_encode(char **av, t_ssl_cmds *cmds);
int				ft_des_check_key(char *key, char *iv);
uint64_t		ft_key_to_bits(char *key);
char			*ft_filled_by_len(char *input);
uint64_t		ft_des_permut(uint64_t nb, uint8_t prm[], int new, int curr);
uint64_t		ft_input_to_bits(char *str);
uint64_t		ft_shuffle_key(uint64_t key, uint8_t i);
uint64_t		ft_shuffle_key_rev(uint64_t key, uint8_t i);
uint64_t		ft_s_boxes(uint64_t inf);
char			*ft_string_from_bits(uint64_t inf);
char			*ft_string_from_bits_r(uint64_t inf, t_ssl_cmds *cmds);
char			*ft_desecb_decode(char **av, t_ssl_cmds *cmds);
char			*ft_ssl_join_block(char *str, char *block, int sz1, int sz2);
char			*ft_des_clear_last_block(char **block, t_ssl_cmds *cmds);

int				ft_descbc(char **av, t_ssl_cmds *cmds);
char			*ft_descbc_encode(char **av, t_ssl_cmds *cmds);
char			*ft_descbc_decode(char **av, t_ssl_cmds *cmds);
uint64_t		ft_descbc_make_vector(char *str);
void			ft_clear_some_mem(t_ssl_cmds *cmds, char **temp, char **fordel,
				char **input);

#endif
