/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 22:08:51 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/15 23:34:07 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memdup(const void *s, size_t i)
{
	void	*str;

	if (!s)
		return (NULL);
	if (!(str = (void*)ft_memalloc(i)))
		return (NULL);
	ft_memcpy(str, s, i);
	return (str);
}
