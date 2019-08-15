/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreepush.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:04:31 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 01:03:29 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	ft_btreepush(t_btree **root, void *item, int (*cmpf)(void *, void *))
{
	if (root && *root)
	{
		if ((*cmpf)(item, (*root)->item) < 0)
			ft_btreepush(&((*root)->left), item, cmpf);
		else
			ft_btreepush(&((*root)->right), item, cmpf);
	}
	else
		*root = ft_btreecreate(item);
}
