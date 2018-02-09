/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 20:59:39 by pzubar            #+#    #+#             */
/*   Updated: 2018/02/08 20:59:46 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <locale.h>
# include <limits.h>

typedef struct		s_inf
{
	char			fl[5];
	int				fw;
	int				pr;
	char			*mf;
	char			sp;
}					t_inf;

typedef struct		s_uni
{
	char			*res;
	unsigned char	one;
	unsigned char	two;
	unsigned char	thr;
	unsigned char	fo;
}					t_uni;

void				ft_parser(va_list ars, char **val, char s, t_inf **in);
void				ft_width(va_list ars, char *s, t_inf *in);
void				ft_flags(char *s, t_inf *in);
void				ft_precision(char *s, t_inf *in);
void				ft_modifier(char *s, t_inf *in);
int					ft_comp(char *arg, t_inf *in, int len);
char				*ft_strfill(char **arr, char c, char *arg, t_inf *in);
char				*ft_itoabase(size_t num, size_t base, int up);
int					ft_isflag(char p, char c);
char				*ft_work_precstr(char *arg, t_inf *in);
char				*ft_nolocale(wchar_t *a, t_inf *in, int len, char *s);
int					ft_int(va_list arg, t_inf *in, int len);
int					ft_unint(va_list arg, t_inf *in, int len);
int					ft_string(void *str, t_inf *in, int len);
char				*ft_utf(wchar_t *a, t_inf *in, int i);
int					ft_zeronly(char *res, char *arg, t_inf *in, int len);
void				ft_addpr(char **arr, char *arg, t_inf *in);
void				ft_addfw(char **arr, char *arg, t_inf *in, size_t len);

#endif
