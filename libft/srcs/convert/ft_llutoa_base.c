/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llutoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 11:35:24 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 22:37:27 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"
#include "str.h"
#include "utils.h"

static int				ft_countllu(unsigned long nb, int len)
{
	int				i;

	if (nb == 0)
		return (1);
	i = 0;
	while (nb)
	{
		nb /= len;
		i++;
	}
	return (i);
}

char					*ft_llutoa_base(unsigned long long nb, const char *base)
{
	char				*str;
	int					i;
	int					len;
	unsigned long long	x;

	x = (unsigned long long)nb;
	len = ft_strlen(base);
	i = ft_countllu(x, len);
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (i--)
	{
		str[i] = base[ft_abs(x % len)];
		x /= len;
	}
	return (str);
}
