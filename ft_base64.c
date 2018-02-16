/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:23:06 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/30 13:23:07 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

// char	*ft_base64_decode(char *input)
// {
// 	const char	base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
// 	uint32_t	convert;
// 	char		*res;
// 	char		*temp;
// 	char		*fordel;
// 	int			i;
// 	int			j;

// 	res = ft_strnew(0);
// 	while (*input)
// 	{
// 		i = 0;
// 		convert = 0;
// 		while (i < 4)
// 		{
// 			j = 0;
// 			if (*(input + i) != '=')
// 				while (*(input + i) != base64[j] && j < 64)
// 					j++;
// 			convert = convert | j;
// 			convert <<= 6;
// 			i++;
// 		}
// 		convert <<= 2;
// 		temp = ft_strnew(3);
// 		i = 0;
// 		while (i < 3)
// 		{
// 			temp[i] = convert >> (24 - 8 * i) & 255;
// 			i++;
// 		}
// 		fordel = res;
// 		res = ft_strjoin(res, temp);
// 		ft_strdel(&fordel);
// 		ft_strdel(&temp);
// 		input += 4;
// 	}
// 	return (res);
// }

// char	*ft_base64_encode(char *input)
// {
// 	uint32_t	convert;
// 	char		*res;
// 	char		*temp;
// 	char		*fordel;
// 	int			i;
// 	int			move;
// 	int			len;
// 	int			res_len;

// 	if (!input)
// 		return (NULL);
// 	res = ft_strnew(0);
// 	move = 0;
// 	len = ft_strlen(input);
// 	while (move <= len - 1)
// 	{
// 		convert = 0;
// 		i = 0;
// 		while (i < 3)
// 		{
// 			if (*(input + i))
// 				convert = convert | input[i];
// 			convert <<= 8;
// 			i++;
// 		}
// 		temp = ft_strnew(4);
// 		i = 0;
// 		while (i < 4)
// 		{
// 			temp[i] = base64[(convert >> (26 - 6 * i)) & 63];
// 			i++;
// 		}
// 		fordel = res;
// 		res = ft_strjoin(res, temp);
// 		ft_strdel(&fordel);
// 		ft_strdel(&temp);
// 		input += 3;
// 		move += 3;
// 	}
// 	if (len % 3 != 0)
// 	{
// 		res_len = ft_strlen(res);
// 		if (len % 3 == 2)
// 			res[res_len - 1] = '=';
// 		else
// 		{
// 			res[res_len - 1] = '=';
// 			res[res_len - 2] = '=';
// 		}
// 	}
// 	return (res);
// }

uint32_t		ft_str_to_32bits(char *str)
{
	int			i;
	uint32_t	ret;

	i = 0;
	ret = 0;
	while (*str)
	{
		ret <<= 8;
		ret |= str [i];
		str++;
	}
	return (ret);
}

char			*ft_base64_encode_block(char *str)
{
	uint32_t	conv;
	int			i;
	char		*ret;

	ret = ft_strnew(4);
	i = 0;
	conv = 0;
	while (*str)
	{
		conv <<= 8;
		conv |= str[i];
		str++;
	}
	i = -1;
	while (++i < 4)
		ret[i] = g_base64[(conv >> (26 - 6 * i)) & 63];
	return (ret);
}

int 		ft_base64_encode(int ac, char **av, t_ssl_cmds *cmds, int *ret)
{
	int		fd;
	int		rd;
	char	buf[RDBS64 + 1];
	char	*res;
	char	*temp;
	char	*fordel;

	ret = 0;
	fd = 0;
	if (cmds->in)
		fd = open(av[cmds->keypos], O_RDONLY);
	res = ft_strnew(4);
	while ((rd = read(fd, buf, RDBS64)) > 0)
	{
		buf[rd] = '\0';
		temp = ft_base64_encode_block(buf);
		fordel = res;
		res = ft_strjoin(res, temp);
		ft_strdel(&temp);
		ft_bzero(buf, RDBS64 + 1);
	}
}

int		ft_base64(int ac, char **av, t_ssl_cmds *cmds)
{
	int	ret;
	
	ret = 0;
	if (cmds->decr)
		ft_base64_encode(ac, av, cmds, &ret);
	// else
	// 	ft_base64_decode(ac, av, cmds, &ret);
	return (ret);
}
