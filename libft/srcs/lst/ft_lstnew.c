/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:57:48 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 22:47:02 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "mem.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*t;

	if ((t = (t_list*)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content)
	{
		if (!(t->content = (void*)ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(t->content, content, content_size);
		t->content_size = content_size;
	}
	else
	{
		t->content = NULL;
		t->content_size = 0;
	}
	t->next = NULL;
	return (t);
}
