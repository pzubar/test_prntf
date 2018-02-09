/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nums.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 21:02:21 by pzubar            #+#    #+#             */
/*   Updated: 2018/02/07 21:02:24 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stddef.h>

char	*ft_ltoa(ptrdiff_t n)
{
	char		*new;
	int			i;
	int			sign;
	uintptr_t	nb;

	sign = (n < 0) ? -1 : 1;
	i = 1;
	nb = ((sign < 0) ? (n * -1) : n);
	while ((n = (n / 10)) != 0)
		i++;
	i = ((sign < 0) ? (i + 1) : i);
	if (!(new = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	new[i] = '\0';
	while (i--)
	{
		new[i] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (sign < 0)
		new[0] = '-';
	return (new);
}

int		ft_int(va_list arg, t_inf *in, int len)
{
	char		*s;

	s = NULL;
	if (!in->mf && in->sp != 'D')
		s = ft_itoa(va_arg(arg, int));
	else if (in->sp == 'D' || ft_strstr(in->mf, "ll"))
		s = ft_ltoa((long long)va_arg(arg, void*));
	else if (ft_strstr(in->mf, "hh"))
		s = ft_itoa((signed char)va_arg(arg, void*));
	else if (ft_strchr(in->mf, 'h'))
		s = ft_itoa((short)va_arg(arg, void*));
	else if (ft_strchr(in->mf, 'l'))
		s = ft_ltoa((long)va_arg(arg, void*));
	else if (ft_strchr(in->mf, 'j'))
		s = ft_ltoa((intmax_t)va_arg(arg, void*));
	else if (ft_strchr(in->mf, 'z'))
		s = ft_ltoa((ssize_t)va_arg(arg, void*));
	else if (ft_strchr(in->mf, 't'))
		s = ft_ltoa((ptrdiff_t)va_arg(arg, void*));
	if (ft_strequ(s, "0") && in->pr < 0)
		s[0] = 0;
	len = len + ft_comp(s, in, len);
	(s) ? ft_strdel(&s) : 0;
	return (len);
}

char	*ft_add_analmf(va_list arg, t_inf *in, char *s)
{
	if (ft_strequ(in->mf, "ll") && (in->sp == 'o'))
		s = ft_itoabase((unsigned long long)va_arg(arg, void *), 8, 0);
	else if (ft_strequ(in->mf, "ll") && (in->sp == 'u'))
		s = ft_itoabase((unsigned long long)va_arg(arg, void *), 10, 0);
	else if (ft_strequ(in->mf, "ll") && (in->sp == 'x' || in->sp == 'X'))
		s = ft_itoabase((unsigned long long)va_arg(arg, void *),\
						16, in->sp == 'x' ? 0 : 1);
	else if (ft_strequ(in->mf, "j") && (in->sp == 'o'))
		s = ft_itoabase((uintmax_t)va_arg(arg, void *), 8, 0);
	else if (ft_strequ(in->mf, "j") && (in->sp == 'u'))
		s = ft_itoabase((uintmax_t)va_arg(arg, void *), 10, 0);
	else if (ft_strequ(in->mf, "j") && (in->sp == 'x' || in->sp == 'X'))
		s = ft_itoabase((uintmax_t)va_arg(arg, void *),\
						16, in->sp == 'x' ? 0 : 1);
	else if (ft_strequ(in->mf, "z") && (in->sp == 'o'))
		s = ft_itoabase((size_t)va_arg(arg, void *), 8, 0);
	else if (ft_strequ(in->mf, "z") && (in->sp == 'u'))
		s = ft_itoabase((size_t)va_arg(arg, void *), 10, 0);
	else if (ft_strequ(in->mf, "z") && (in->sp == 'x' || in->sp == 'X'))
		s = ft_itoabase((size_t)va_arg(arg, void *),\
						16, in->sp == 'x' ? 0 : 1);
	else if (ft_strequ(in->mf, "t") && (in->sp == 'x' || in->sp == 'X'))
		s = ft_itoabase((uintptr_t)va_arg(arg, void *),\
						16, in->sp == 'x' ? 0 : 1);
	return (s);
}

char	*ft_analmf(va_list arg, t_inf *in, char *s)
{
	if (ft_strequ(in->mf, "hh") && (in->sp == 'o'))
		s = ft_itoabase((unsigned char)va_arg(arg, void *), 8, 0);
	else if (ft_strequ(in->mf, "hh") && (in->sp == 'u'))
		s = ft_ltoa((unsigned char)va_arg(arg, void *));
	else if (ft_strequ(in->mf, "hh") && (in->sp == 'x' || in->sp == 'X'))
		s = ft_itoabase((unsigned char)va_arg(arg, void *),\
						16, in->sp == 'x' ? 0 : 1);
	else if (ft_strequ(in->mf, "h") && (in->sp == 'o'))
		s = ft_itoabase((unsigned short)va_arg(arg, void *), 8, 0);
	else if (ft_strequ(in->mf, "h") && (in->sp == 'u'))
		s = ft_ltoa((unsigned short)va_arg(arg, void *));
	else if (ft_strequ(in->mf, "h") && (in->sp == 'x' || in->sp == 'X'))
		s = ft_itoabase((unsigned short)va_arg(arg, void *),\
						16, in->sp == 'x' ? 0 : 1);
	else if (ft_strequ(in->mf, "l") && (in->sp == 'o'))
		s = ft_itoabase((unsigned long)va_arg(arg, void *), 8, 0);
	else if (ft_strequ(in->mf, "l") && (in->sp == 'x' || in->sp == 'X'))
		s = ft_itoabase((unsigned long)va_arg(arg, void *),\
						16, in->sp == 'x' ? 0 : 1);
	else if (ft_strequ(in->mf, "t") && (in->sp == 'o' || in->sp == 'u'))
		s = ft_itoabase((uintptr_t)va_arg(arg, void *), in->sp == 'o' ?\
			8 : 10, 0);
	else
		s = ft_add_analmf(arg, in, s);
	return (s);
}

int		ft_unint(va_list arg, t_inf *in, int len)
{
	char *s;

	s = NULL;
	(in)->fl[1] = '0';
	(in)->fl[2] = '0';
	if ((in)->sp == 'U' || (ft_strequ(in->mf, "l") && (in->sp == 'u')))
		s = ft_itoabase((uintptr_t)va_arg(arg, void *), 10, 0);
	else if ((in)->sp == 'O')
		s = ft_itoabase((uintptr_t)va_arg(arg, void *), 8, 0);
	else if (!(in)->mf && ((in)->sp == 'o'))
		s = ft_itoabase((unsigned int)va_arg(arg, void *), 8, 0);
	else if (!(in)->mf && (in->sp == 'u'))
		s = ft_ltoa((unsigned int)va_arg(arg, void *));
	else if (!(in)->mf && (in)->sp == 'x')
		s = ft_itoabase((unsigned int)va_arg(arg, void *), 16, 0);
	else if (!(in)->mf && (in)->sp == 'X')
		s = ft_itoabase((unsigned int)va_arg(arg, void *), 16, 1);
	else if ((in)->sp == 'p')
		s = ft_itoabase((unsigned long long)va_arg(arg, void*), 16, 0);
	else if (in->mf)
		s = ft_analmf(arg, in, s);
	s[0] = (ft_strequ(s, "0") && (in)->pr < 0) ? 0 : s[0];
	len = len + ft_comp(s, (in), len);
	(s) ? ft_strdel(&s) : 0;
	return (len);
}
