/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 22:07:19 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/15 21:14:40 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tmp;

	tmp = (char*)dst;
	while (n--)
		*(tmp++) = *((char*)src++);
	return (dst);
}
