/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:07:54 by pzubar            #+#    #+#             */
/*   Updated: 2018/02/08 20:07:56 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <wchar.h>
#include <stddef.h>
#include "ft_printf.h"

void	ft_addpr(char **arr, char *arg, t_inf *in)
{
	char	*tmp;
	size_t	len;

	len = (arg[0] == '-') ? ft_strlen(arg) - 1 : ft_strlen(arg);
	if (in->pr > (int)len && len > 0)
	{
		len = in->pr - len;
		tmp = ft_strnew(len);
		while (len--)
			tmp[len] = '0';
		*arr = ft_strjoin(tmp, arg);
		ft_strdel(&tmp);
	}
}

int		ft_char(int r, t_inf *in, int len)
{
	char	*arg;
	int		c;
	wchar_t	a;

	arg = NULL;
	if (in->sp == 'C')
	{
		a = r;
		c = (unsigned char)r;
		if (MB_CUR_MAX == 4)
			arg = ft_utf(&a, in, 1);
		if (!arg && (arg = ft_strnew(1)))
			arg[0] = c;
		in->pr = 0;
	}
	else
	{
		c = (unsigned char)r;
		arg = ft_strnew(1);
		arg[0] = c;
	}
	len = len + ft_comp(arg, in, len);
	(arg) ? ft_strdel(&arg) : 0;
	return (len);
}

int		ft_worktype(va_list ars, int len, char c, t_inf *in)
{
	if (c == 's' || c == 'S')
		len = ft_string((void*)va_arg(ars, void*), in, len);
	else if (c == 'c' || c == 'C')
		len = ft_char((wint_t)va_arg(ars, void*), in, len);
	else if (c == 'x' || c == 'X' || c == 'p' || c == 'o' \
			|| c == 'O' || c == 'u' || c == 'U')
		len = ft_unint(ars, in, len);
	else if (c == 'd' || c == 'D' || c == 'i')
		len = ft_int(ars, in, len);
	else if (c == '%')
		len = ft_string("%", in, len);
	else
		len = ft_char(c, in, len);
	return (len);
}

int		ft_typefinder(va_list ars, int *len, const char *fmt, int i)
{
	int		s;
	t_inf	*in;
	char	*arr;

	s = i;
	while (fmt[s++])
	{
		if (fmt[s] == 'n' && (*(va_arg(ars, int*)) = *len) >= 0)
			break ;
		else if (ft_isflag(0, fmt[s]) == 4 || \
			(!ft_isflag(fmt[s - 1], fmt[s]) && ft_isprint(fmt[s])))
		{
			arr = ft_strsub(fmt, i + 1, s - i);
			ft_parser(ars, &arr, fmt[s], &in);
			*len = ft_worktype(ars, *len, fmt[s], in);
			(in->mf) ? ft_strdel(&in->mf) : 0;
			ft_strdel(&arr);
			free(in);
			break ;
		}
		if (!ft_isprint(fmt[s]) && (s--) >= 0)
			break ;
	}
	return (s);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (format)
	{
		va_start(ap, format);
		while (format[i])
		{
			if (format[i] == '%')
				i = ft_typefinder(ap, &len, format, i);
			else if (++len)
				write(1, &format[i], 1);
			i++;
		}
	}
	va_end(ap);
	return (len);
}
