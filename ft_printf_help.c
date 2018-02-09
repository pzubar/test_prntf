/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:17:26 by pzubar            #+#    #+#             */
/*   Updated: 2018/01/18 18:17:27 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_zeronly(char *res, char *arg, t_inf *in, int len)
{
	ft_addfw(&res, arg, in, ft_strlen(arg));
	(res && in->fl[0] == '0') ? ft_putstr(res) : 0;
	ft_putchar(0);
	(res && in->fl[0] == '1') ? ft_putstr(res) : 0;
	len = (res) ? (int)ft_strlen(res) + 1 : 1;
	(res) ? ft_strdel(&res) : 0;
	return (len);
}

char	*ft_itoabase(size_t num, size_t base, int up)
{
	char	*hex;
	char	*res;
	size_t	tmp;
	int		i;

	hex = (up) ? "0123456789ABCDEF" : "0123456789abcdef";
	i = 1;
	tmp = num;
	while ((tmp = tmp / base) != 0)
		i++;
	res = (char*)malloc(sizeof(char) * i + 1);
	res[i--] = '\0';
	while (num >= base)
	{
		res[i--] = hex[num % base];
		num = num / base;
	}
	res[i--] = hex[num % base];
	return (res);
}

int		ft_isflag(char p, char c)
{
	if (c == 's' || c == 'S' || c == 'c' || c == 'C' || c == 'd' || c == 'D' ||\
		c == 'i' || c == 'x' || c == 'X' || c == 'p' || c == 'o' || c == 'O' ||\
		c == 'u' || c == 'U' || c == '%')
		return (4);
	if (c == 45 || (c == 48 && (!ft_isdigit(p))) || c == 35)
		return (1);
	if (c == 32 || c == 46 || c == 43 || c == '*')
		return (1);
	if (ft_isdigit(c))
		return (2);
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == 't')
		return (3);
	return (0);
}

char	*ft_work_precstr(char *arg, t_inf *in)
{
	char		*buf;

	buf = NULL;
	if (in->sp == '%')
		return (ft_strdup("%"));
	if (in->pr < 0)
	{
		if ((in->sp == 'S') && MB_CUR_MAX != 4)
			ft_strdel(&arg);
		return (ft_strdup(""));
	}
	if (!arg)
		return (in->pr ? ft_strsub("(null)", 0, in->pr) : ft_strdup("(null)"));
	if ((in->sp == 'S') && MB_CUR_MAX == 4)
		return (arg);
	else if ((in->sp == 'S') && MB_CUR_MAX != 4)
	{
		buf = (in->pr) ? ft_strsub(arg, 0, in->pr) : ft_strdup(arg);
		ft_strdel(&arg);
	}
	if (!in->pr && in->sp != 'S')
		return (ft_strdup(arg));
	buf = (!buf) ? ft_strsub(arg, 0, in->pr) : buf;
	in->pr = 0;
	return (buf);
}

char	*ft_nolocale(wchar_t *a, t_inf *in, int len, char *s)
{
	while (a[len])
		len++;
	s = ft_strnew(len++);
	while (len--)
		s[len] = a[len];
	s = ft_work_precstr(s, in);
	return (s);
}
