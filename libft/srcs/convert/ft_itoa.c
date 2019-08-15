/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:35:07 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 22:40:48 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"
#include "str.h"
#include "utils.h"

static int		ft_count(int nb)
{
	int		i;

	if (nb == 0)
		return (1);
	i = (nb < 0) ? 1 : 0;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int nb)
{
	char	*str;
	int		i;
	int		neg;

	neg = (nb < 0) ? -1 : 1;
	i = ft_count(nb);
	if (!(str = ft_strnew(i)))
		return (NULL);
	while (i--)
	{
		str[i] = ft_abs(nb % 10) + '0';
		nb /= 10;
	}
	if (neg < 0)
		str[0] = '-';
	return (str);
}
