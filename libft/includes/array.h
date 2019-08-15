/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 00:50:15 by fbabin            #+#    #+#             */
/*   Updated: 2019/08/14 21:53:49 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

typedef struct		s_mparams
{
	int				left;
	int				right;
}					t_mparams;

/*
** --------------------------- ARRAY FUNCTIONS ----------------------------
*/

int					ft_qs_intcmp(void *n1, void *n2);
int					ft_qs_strcmp(void *s1, void *s2);

void				ft_dumpint(void *nb);
void				ft_dumpstr(void *s);

char				*ft_join(char **tab, char *sep);
void				ft_quicksort(void **array, int left, int right,
						int (cmp)(void*, void*));
void				ft_mergesort(void **array, int left, int right,
						int (cmp)(void*, void*));
void				ft_array_dump(void **array, int len, void (dump)(void*));

#endif
