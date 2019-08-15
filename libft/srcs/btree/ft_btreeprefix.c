/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreeprefix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:19:50 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 01:03:09 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		ft_btreeprefix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		applyf(root->item);
		ft_btreeprefix(root->left, applyf);
		ft_btreeprefix(root->right, applyf);
	}
}
