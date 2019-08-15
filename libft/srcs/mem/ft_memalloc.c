/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 22:04:57 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/15 21:15:45 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memalloc(size_t size)
{
	void	*str;

	if (!(str = (void*)malloc(size * sizeof(void))))
		return (NULL);
	ft_bzero(str, size);
	return (str);
}
