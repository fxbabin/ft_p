/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcreate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 21:52:16 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 22:28:13 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"
#include "mem.h"

t_list		*ft_lstcreate(void *content, size_t cs)
{
	t_list	*t;

	if (!(t = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	t->content = content;
	t->content_size = cs;
	t->next = NULL;
	return (t);
}
