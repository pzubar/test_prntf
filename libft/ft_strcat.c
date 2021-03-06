/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzubar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:27:40 by pzubar            #+#    #+#             */
/*   Updated: 2017/10/30 15:27:43 by pzubar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (dst[i])
	{
		i++;
	}
	while (src[n])
	{
		dst[i] = src[n];
		i++;
		n++;
	}
	dst[i] = '\0';
	return (dst);
}
