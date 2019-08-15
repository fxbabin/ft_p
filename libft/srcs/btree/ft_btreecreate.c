/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 15:25:19 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 01:02:17 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"
#include "mem.h"

t_btree		*ft_btreecreate(void *item)
{
	t_btree		*bt;

	if (!(bt = (t_btree*)ft_memalloc(sizeof(t_btree))))
		return (NULL);
	bt->item = item;
	bt->left = NULL;
	bt->right = NULL;
	return (bt);
}
