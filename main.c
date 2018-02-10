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

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <inttypes.h>
#include "libftprintf.h"

int		ft_print_usage(void);
char	*ft_base64_encode(char *input);
char	*ft_base64_decode(char *input);


int		main(int ac, char **av)
{
	char *hh;

	if (ac == 4 && !ft_strcmp(av[1], "base64") && !ft_strcmp(av[2], "-e"))
		hh = ft_base64_encode(av[3]);
	else if (ac == 4 && !ft_strcmp(av[1], "base64") && !ft_strcmp(av[2], "-d"))
		hh = ft_base64_decode(av[3]);
	else
		return (ft_print_usage());
	ft_printf("result: %s\n", hh);
	ft_strdel(&hh);

	return (0);
}

int		ft_print_usage(void)
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (1);
}

char	*ft_base64_decode(char *input)
{
	const char	base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	uint32_t	convert;
	char		*res;
	char		*temp;
	char		*fordel;
	int			i;
	int			j;

	res = ft_strnew(0);
	while (*input)
	{
		i = 0;
		convert = 0;
		while (i < 4)
		{
			j = 0;
			if (*(input + i) != '=')
				while (*(input + i) != base64[j] && j < 64)
					j++;
			convert = convert | j;
			convert <<= 6;
			i++;
		}
		convert <<= 2;
		temp = ft_strnew(3);
		i = 0;
		while (i < 3)
		{
			temp[i] = convert >> (24 - 8 * i) & 255;
			i++;
		}
		fordel = res;
		res = ft_strjoin(res, temp);
		ft_strdel(&fordel);
		ft_strdel(&temp);
		input += 4;
	}
	return (res);
}

char	*ft_base64_encode(char *input)
{
	const char	base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	uint32_t	convert;
	char		*res;
	char		*temp;
	char		*fordel;
	int			i;
	int			move;
	int			len;
	int			res_len;
	
	if (!input)
		return (NULL);
	res = ft_strnew(0);
	move = 0;
	len = ft_strlen(input);
	while (move <= len - 1)
	{
		convert = 0;
		i = 0;
		while (i < 3)
		{
			if (*(input + i))
				convert = convert | input[i];
			convert <<= 8;
			i++;
		}
		temp = ft_strnew(4);
		i = 0;
		while (i < 4)
		{
			temp[i] = base64[(convert >> (26 - 6 * i)) & 63];
			i++;
		}
		fordel = res;
		res = ft_strjoin(res, temp);
		ft_strdel(&fordel);
		ft_strdel(&temp);
		input += 3;
		move += 3;
	}
	if (len % 3 != 0)
	{
		res_len = ft_strlen(res);
		if (len % 3 == 2)
			res[res_len - 1] = '=';
		else
		{
			res[res_len - 1] = '=';
			res[res_len - 2] = '=';
		}
	}
	return (res);
}
