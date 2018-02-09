/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 21:05:15 by pzubar            #+#    #+#             */
/*   Updated: 2018/02/07 21:05:17 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_wcharadd(uint32_t tmp, t_uni *utf, int sz)
{
	if (sz <= 16 && (utf->res = ft_strnew(3)))
	{
		utf->thr = (tmp << 26) >> 26;
		utf->two = ((tmp >> 6) << 26) >> 26;
		utf->one = ((tmp >> 12) << 28) >> 28;
		utf->res[0] = ((uint32_t)14712960 >> 16) | utf->one;
		utf->res[1] = (((uint32_t)14712960 << 16) >> 24) | utf->two;
		utf->res[2] = (((uint32_t)14712960 << 24) >> 24) | utf->thr;
	}
	else if ((utf->res = ft_strnew(4)))
	{
		utf->fo = (tmp << 26) >> 26;
		utf->thr = ((tmp >> 6) << 26) >> 26;
		utf->two = ((tmp >> 12) << 26) >> 26;
		utf->one = ((tmp >> 18) << 29) >> 29;
		utf->res[0] = ((uint32_t)4034953344 >> 24) | utf->one;
		utf->res[1] = (((uint32_t)4034953344 << 8) >> 24) | utf->two;
		utf->res[2] = (((uint32_t)4034953344 << 16) >> 24) | utf->thr;
		utf->res[3] = (((uint32_t)4034953344 << 24) >> 24) | utf->fo;
	}
	return (utf->res);
}

char	*ft_wchar(wchar_t val, t_uni *utf)
{
	uint32_t		tmp;
	unsigned int	byt;
	int				sz;

	tmp = val;
	byt = val;
	sz = 1;
	while ((byt = (byt / 2)))
		sz++;
	if (sz <= 7 && (utf->res = ft_strnew(1)))
		utf->res[0] = (unsigned char)val;
	else if (sz <= 11 && (utf->res = ft_strnew(2)))
	{
		utf->one = (tmp << 26) >> 26;
		utf->two = ((tmp >> 6) << 27) >> 27;
		utf->res[0] = (unsigned char)((uint32_t)49280 >> 8) | utf->two;
		utf->res[1] = (unsigned char)(((uint32_t)49280 << 24) >> 24) | utf->one;
	}
	else
		utf->res = ft_wcharadd(tmp, utf, sz);
	return (utf->res);
}

char	*ft_utfhelp(wchar_t *a, t_inf *in, t_uni *utf, char *res)
{
	char *buf;
	char *tmp;

	while (*a)
	{
		tmp = ft_wchar(*a, utf);
		buf = (res) ? ft_strdup(res) : NULL;
		ft_strdel(&res);
		if (buf && ((in->pr > 0 && in->pr >= (int)(ft_strlen(buf) +\
			ft_strlen(tmp))) || !in->pr))
			res = ft_strjoin(buf, tmp);
		else if (!buf)
			res = ft_strdup(tmp);
		else
		{
			ft_strdel(&tmp);
			return (buf);
		}
		ft_strdel(&tmp);
		ft_strdel(&buf);
		a++;
	}
	return (res);
}

char	*ft_utf(wchar_t *a, t_inf *in, int i)
{
	t_uni	*utf;
	char	*res;

	if (!(utf = malloc(sizeof(t_uni))))
		return (NULL);
	res = NULL;
	if (!a)
		return (NULL);
	if (i)
		res = ft_wchar(*a, utf);
	else
		res = ft_utfhelp(a, in, utf, res);
	if (!res)
		res = ft_strdup("");
	free(utf);
	return (res);
}

int		ft_string(void *str, t_inf *in, int len)
{
	char		*s;

	s = NULL;
	if (MB_CUR_MAX == 4 && (in->sp == 'S'))
	{
		if (in->pr < 0)
			s = (ft_strdup(""));
		else
		{
			s = ft_utf((wchar_t*)str, in, 0);
			s = ft_work_precstr(s, in);
			in->pr = 0;
		}
	}
	else if (MB_CUR_MAX != 4 && (in->sp == 'S'))
		s = ft_nolocale((wchar_t*)str, in, len, s);
	else
		s = ft_work_precstr((char*)str, in);
	len = (s) ? len + ft_comp(s, in, len) : len;
	(s) ? ft_strdel(&s) : 0;
	return (len);
}
