/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_comp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:14:52 by pzubar            #+#    #+#             */
/*   Updated: 2018/01/18 18:14:54 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define ISPLUS ft_strchr(arg, '+')
#define ISHEX (in->sp == 'x' || in->sp == 'X')
#define ISOCT (in->sp == 'o' || in->sp == 'O')

void	ft_chealt(char **arr, t_inf *in)
{
	char *buf;

	buf = ft_strdup(*arr);
	if ((in->sp == 'x' || in->sp == 'p') && buf[0] == '0')
	{
		if (ft_strchr(buf, 'x') && buf[1] != 'x')
		{
			ft_strdel(arr);
			buf[ft_strchr(buf, 'x') - buf] = '0';
			buf[1] = 'x';
			*arr = ft_strdup(buf);
		}
	}
	else if (in->sp == 'X' && buf[0] == '0')
		if (ft_strchr(buf, 'X') && buf[1] != 'X')
		{
			ft_strdel(arr);
			buf[ft_strchr(buf, 'X') - buf] = '0';
			buf[1] = 'X';
			*arr = ft_strdup(buf);
		}
	ft_strdel(&buf);
}

void	ft_addfw(char **arr, char *arg, t_inf *in, size_t len)
{
	char	*tmp;
	char	*buf;
	char	fil;

	fil = ' ';
	if ((size_t)in->fw > len)
	{
		buf = (*arr) ? ft_strdup(*arr) : ft_strdup(arg);
		(*arr) ? ft_strdel(arr) : 0;
		len = (size_t)in->fw - ft_strlen(buf);
		len = (in->sp == 'c' || in->sp == 'C') && !*arg ? len - 1 : len;
		if (((!in->pr || in->pr < 0)) || (in->sp == 's' &&\
			in->fw > (int)ft_strlen(buf)))
			if (in->fl[4] == '1')
				fil = '0';
		tmp = ft_strnew(len);
		while (len--)
			tmp[len] = fil;
		*arr = (in->fl[0] == '1') ? ft_strjoin(buf, tmp) : ft_strjoin(tmp, buf);
		((in->fl[3] == '1') || in->sp == 'p') ? ft_chealt(arr, in) : 0;
		ft_strdel(&buf);
		ft_strdel(&tmp);
	}
	in->fw = -1;
}

void	ft_addal(char **arr, char *arg, t_inf *in)
{
	char *buf;
	char *al;

	if ((ft_strequ("0", arg) && in->sp != 'p') || (*arr && in->pr <=\
		(int)ft_strlen(*arr) && ISOCT) || (!*arr && !arg[0] && ISHEX))
		return ;
	if (in->sp == 'x' || in->sp == 'X' || in->sp == 'o'\
		|| in->sp == 'O' || in->sp == 'p')
	{
		al = (in->sp == 'X') ? "0X" : "0";
		al = (in->sp == 'x' || in->sp == 'p') ? "0x" : al;
		if (*arr)
		{
			buf = ft_strdup(*arr);
			ft_strdel(arr);
			*arr = ft_strjoin(al, buf);
			ft_strdel(&buf);
		}
		else if (arg)
		{
			buf = ft_strdup(arg);
			*arr = ft_strjoin(al, buf);
			ft_strdel(&buf);
		}
	}
}

void	ft_addsi(char **arr, char *arg, t_inf *in, int len)
{
	if (in->fw == -1)
	{
		arg = *arr;
		while (arg && *arg == ' ')
			arg++;
		if (arg && arg[0] == '0' && (ISPLUS || ft_strchr(arg, '-')))
		{
			len = ISPLUS ? ISPLUS - arg : ft_strrchr(arg, '-') - arg;
			arg[0] = ft_strchr(arg, '+') ? '+' : '-';
			arg[len] = '0';
		}
		return ;
	}
	if (in->sp != 'i' && in->sp != 'd' && in->sp != 'D')
		return ;
	if (*arr && !ft_strchr(*arr, '-'))
	{
		arg = ft_strdup(*arr);
		ft_strdel(arr);
		*arr = (in->fl[1] == '1') ? ft_strjoin("+", arg) : ft_strjoin(" ", arg);
		ft_strdel(&arg);
	}
	else if (arg && !ft_strchr(arg, '-'))
		*arr = (in->fl[1] == '1') ? ft_strjoin("+", arg) : ft_strjoin(" ", arg);
}

int		ft_comp(char *arg, t_inf *in, int len)
{
	char *res;

	if (!(res = NULL) && (in->sp == 'c' || in->sp == 'C') && (!arg || !*arg))
		return (ft_zeronly(res, arg, in, len));
	in->sp != 'c' && in->sp != '%' ? ft_addpr(&res, arg, in) : 0;
	(in->fl[1] == '1' || in->fl[2] == '1') ? ft_addsi(&res, arg, in, len) : 0;
	((in->fl[3] == '1') || in->sp == 'p') ? ft_addal(&res, arg, in) : 0;
	ft_addfw(&res, arg, in, (res) ? ft_strlen(res) : ft_strlen(arg));
	ft_addsi(&res, arg, in, len);
	if (in->fl[2] == '1' && res && res[0] == '0' && ft_strchr(res, ' ')\
		&& in->sp != 's')
	{
		res[ft_strchr(res, ' ') - res] = '0';
		res[0] = ' ';
	}
	(res) ? ft_putstr(res) : ft_putstr(arg);
	len = (res) ? (int)ft_strlen(res) : (int)ft_strlen(arg);
	ft_strdel(&res);
	return (len);
}
