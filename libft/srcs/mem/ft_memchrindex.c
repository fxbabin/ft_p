/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchrindex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 23:19:52 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/17 15:51:20 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

size_t		ft_memchrindex(const void *s, int c, size_t n)
{
	size_t		index;

	index = 0;
	while (n--)
	{
		if (*((unsigned char*)s) == (unsigned char)c)
			return (index);
		s++;
		index++;
	}
	return (index);
}
