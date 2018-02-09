/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 12:48:30 by pzubar            #+#    #+#             */
/*   Updated: 2018/01/17 12:48:32 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

#define ISWID !ft_isdigit(s[i - 1])

void	ft_modifier(char *s, t_inf *in)
{
	in->mf = NULL;
	if (!s)
		return ;
	if (ft_strchr(s, 't'))
		in->mf = ft_strdup("t");
	if (ft_strchr(s, 'z'))
		in->mf = ft_strdup("z");
	else if (ft_strchr(s, 'j'))
		in->mf = ft_strdup("j");
	else if (ft_strstr(s, "ll"))
		in->mf = ft_strdup("ll");
	else if (ft_strchr(s, 'l'))
		in->mf = ft_strdup("l");
	else if (ft_strstr(s, "hh"))
		in->mf = ft_strdup("hh");
	else if (ft_strchr(s, 'h'))
	{
		s = s + (ft_strchr(s, 'h') - s + 1);
		while (ft_isflag(0, *s) && ft_isflag(0, *s) != 3)
			s++;
		if (*s == 'h')
			in->mf = ft_strdup("hh");
		else
			in->mf = ft_strdup("h");
	}
}

void	ft_precision(char *s, t_inf *in)
{
	int		i;

	if (in->pr < 0)
	{
		in->pr = 0;
		return ;
	}
	if (in->pr)
		return ;
	if (!s || !ft_strrchr(s, '.'))
		return ;
	i = (int)(ft_strrchr(s, '.') - s + 1);
	if (!ft_isdigit(s[i]))
	{
		in->pr = (s[i] == '0') ? -2 : -1;
		return ;
	}
	else
	{
		in->pr = ft_atoi(&s[i]);
		in->pr = (!in->pr) ? -1 : in->pr;
		in->fl[0] = (!in->fw) ? '0' : in->fl[0];
	}
}

void	ft_flags(char *s, t_inf *in)
{
	int	i;
	int	n;

	in->fl[0] = (ft_strchr(s, '-') ? '1' : '0');
	in->fl[1] = (ft_strchr(s, '+') && (in->sp == 'D' || in->sp == 'd' ||\
		in->sp == 'i' || in->sp == 'u' || in->sp == 'U') ? '1' : '0');
	in->fl[2] = (ft_strchr(s, ' ') && in->fl[1] == '0') ? '1' : '0';
	in->fl[3] = (ft_strchr(s, '#') ? '1' : '0');
	if (in->fl[0] == '0' && !(i = 0))
		while ((s = &s[i]) && s[0])
		{
			if (in->fl[4] == '1')
				break ;
			in->fl[4] = (i == 0 && s[i] == '0') ? '1' : in->fl[4];
			if (ft_strchr(s, '0') && ((n = (int)\
				(ft_strchr(s, '0') - s - 1) >= 0)))
				in->fl[4] = (!ft_isdigit(s[n - 1]) &&\
					s[n - 1] != '.') ? '1' : in->fl[4];
			i++;
		}
	if (in->fl[4] != '1')
		in->fl[4] = '0';
}

void	ft_width(va_list ars, char *s, t_inf *in)
{
	int		i;
	int		arg;

	in->fw = 0;
	in->pr = 0;
	i = 0;
	while (s[i])
	{
		if ((ft_isdigit(s[i])) || s[i] == '*')
		{
			arg = (s[i] == '*') ? (int)va_arg(ars, void*) : ft_atoi(&s[i]);
			if (s[i - 1] != '.' && ((ft_atoi(&s[i]) && ISWID) || s[i] == '*'))
			{
				in->fl[0] = (arg < 0) ? '1' : in->fl[0];
				arg = (arg < 0) ? arg * -1 : arg;
				in->fw = (s[i] == '*') ? arg : ft_atoi(&s[i]);
			}
			if (s[i - 1] == '.' && s[i] == '*')
			{
				arg = (arg < 0) ? -1 : arg;
				in->pr = arg;
			}
		}
		i++;
	}
}

void	ft_parser(va_list ars, char **val, char s, t_inf **in)
{
	(*in) = (t_inf*)malloc(sizeof(t_inf));
	(*in)->sp = (ft_isflag(0, s) == 4) ? s : 'c';
	ft_flags(*val, (*in));
	ft_width(ars, *val, (*in));
	ft_precision(*val, (*in));
	ft_modifier(*val, (*in));
	if ((*in)->pr && ((*in)->sp == 'd' || (*in)->sp == 'i' ||\
		(*in)->sp == 'D' || (*in)->sp == 'O' || (*in)->sp == 'o' ||\
		(*in)->sp == 'u' || (*in)->sp == 'x' || (*in)->sp == 'X' ||\
		(*in)->sp == 'U'))
		(*in)->fl[4] = '0';
	if (ft_strequ((*in)->mf, "l"))
	{
		((*in)->sp == 's') ? (*in)->sp = 'S' : 0;
		((*in)->sp == 'c') ? (*in)->sp = 'C' : 0;
	}
	if ((*in)->sp == 's' || (*in)->sp == 'S' || (*in)->sp == 'c' ||\
		(*in)->sp == 'C')
		(*in)->fl[1] = '0';
}
