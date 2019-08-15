/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 22:09:06 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/15 23:59:04 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*d;
	const char		*s;

	if (dest <= src)
		ft_memcpy(dest, src, n);
	else
	{
		d = dest + n - 1;
		s = src + n - 1;
		while (n--)
			*(d--) = *(s--);
	}
	return (dest);
}
