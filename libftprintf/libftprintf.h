/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 16:10:14 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/12 16:21:10 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <inttypes.h>
# include "./libft/libft.h"

typedef struct	s_params
{
	char		f_min;
	char		f_plus;
	char		f_space;
	char		f_zero;
	char		f_sharp;
	int			width;
	char		dot;
	int			prec;
	int			len;
	char		conv;
}				t_params;

int				ft_printf(char *s, ...);
void			ft_parse_printf(char **s, t_params *params, va_list ap);
char			*ft_get_int(t_params *params, va_list ap);
char			*ft_get_longint(t_params *params, va_list ap);
char			*ft_get_octal(t_params *params, va_list ap);
char			*ft_get_longoctal(t_params *params, va_list ap);
char			*ft_get_hexadec(t_params *params, va_list ap);
char			*ft_get_unsign(t_params *params, va_list ap);
char			*ft_get_longunsign(t_params *params, va_list ap);
char			*ft_get_ptr(t_params *params, va_list ap);
char			*ft_get_binary(va_list ap);
char			*ft_get_char_str_perc(char **temp, char conv, va_list ap);
void			ft_apply_flags(char **temp, t_params *params);
void			ft_apply_precision(char **temp, t_params *params);
void			ft_prec_for_positive(char **temp, t_params *params);
void			ft_prec_for_negative(char **temp, t_params *params);
void			ft_apply_width(char **temp, t_params *params);
void			ft_apply_sharp(char **str, t_params *params);
void			ft_apply_space(char **str, t_params *params);
void			ft_apply_plus(char **str, t_params *params);
void			ft_apply_zero(char **str, t_params *params);
void			ft_zero_nonptr(char **str, t_params *params, int i);
char			*ft_get_unichar(uint uni);
char			*ft_get_unistr(va_list ap);
char			*ft_unicode_arg(t_params *params, va_list ap);
char			*ft_typical_arg(t_params *params, va_list ap);
void			ft_sharp_octal_hexa(char **str, t_params *params);

#endif
