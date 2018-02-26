/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_desfuncs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 18:25:34 by abodnar           #+#    #+#             */
/*   Updated: 2018/02/20 18:25:35 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include "ft_ssl_globals.h"

char			*ft_des_clear_last_block(char **block, t_ssl_cmds *cmds)
{
	int			new_size;
	char		*ret;

	if ((*block)[7] > 0 && (*block)[7] < 9)
	{
		new_size = 8 - (*block)[7];
		cmds->curr_block = new_size;
		ret = ft_strsub(*block, 0, new_size);
		ft_strdel(block);
		return (ret);
	}
	else
		return (*block);
}

char			*ft_filled_by_len(char *input)
{
	size_t		len;
	int			i;
	char		*res;

	len = ft_strlen(input);
	if (len == 0)
		return (ft_strdup(EIGHTED));
	else if (len >= 8)
		return (ft_strsub(input, 0, 8));
	else
	{
		res = ft_strnew(8);
		i = 8 - len;
		res = ft_memset(res, i, 8);
		res = ft_memcpy(res, (const void*)input, len);
		return (res);
	}
}

uint64_t		ft_s_boxes(uint64_t inf)
{
	int			i;
	uint64_t	res;
	uint64_t	temp;

	res = 0;
	i = -1;
	while (++i < 8)
	{
		res <<= 4;
		temp = inf >> (42 - i * 6) & 63;
		res = res | g_six_to_four[i][(CENTR4OF6(temp)) | ((FL2OF6(temp)) << 4)];
	}
	return (res);
}
