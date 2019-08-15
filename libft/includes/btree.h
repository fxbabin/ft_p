/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 00:56:28 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 00:57:52 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

/*
** --------------------------------- STRUCTURES -------------------------------
*/

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

/*
** --------------------------- BTREE FUNCTIONS --------------------------------
*/

t_btree				*ft_btreecreate(void *item);
void				ft_btreepush(t_btree **root, void *item,
						int (*cmpf)(void *, void *));
void				ft_btreeprefix(t_btree *root, void (*applyf)(void *));
void				ft_btreeinfix(t_btree *root, void (*applyf)(void *));
void				ft_btreepostfix(t_btree *root, void (*applyf)(void *));

#endif
