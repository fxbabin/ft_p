/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 22:23:45 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 22:18:09 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "mem.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char*)ft_memalloc(size + 1)))
		return (NULL);
	return (str);
}
