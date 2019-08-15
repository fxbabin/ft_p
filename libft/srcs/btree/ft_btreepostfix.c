/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreepostfix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 17:30:37 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 01:02:54 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	ft_btreepostfix(t_btree *root, void (*applyf)(void *))
{
	if (root)
	{
		ft_btreepostfix(root->left, applyf);
		ft_btreepostfix(root->right, applyf);
		applyf(root->item);
	}
}
