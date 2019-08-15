/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:28:56 by fbabin            #+#    #+#             */
/*   Updated: 2019/06/17 15:27:57 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"
#include "mem.h"
#include "str.h"

int				ft_llcount(long long nb)
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

static void		null_decimal(char **str, int prec)
{
	size_t		len;

	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	while (prec--)
		ft_strcpy(*str + len++, "0");
}

static void		precision_handler(char **str, double nb, int prec)
{
	char		*tmp;

	while (prec--)
	{
		nb *= 10;
		if (!prec && (long long)((nb - (long long)nb) * 10) >= 5
				&& (long long)((nb - (long long)nb) * 10) != 9)
			nb += 1;
		ft_strcat(*str, tmp = ft_lltoa(nb));
		ft_strdel(&tmp);
		nb -= (long)nb;
	}
}

char			*ft_ftoa(double nb, int prec)
{
	char		*str;
	char		*tmp;
	size_t		len;

	prec = (prec < 0) ? 0 : prec;
	len = ft_llcount(nb) + prec + 1;
	if (!(str = (char *)ft_memalloc((len + 1) * sizeof(char))))
		return (NULL);
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	ft_strcat(str, tmp = ft_lltoa(nb));
	ft_strdel(&tmp);
	if (prec)
	{
		ft_strcat(str, ".");
		if ((nb = nb - (long long)nb))
			precision_handler(&str, nb, prec);
		else
			null_decimal(&str, prec);
	}
	return (str);
}
