/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 22:10:14 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/20 15:55:28 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "mem.h"

static void		ft_merge(void **array, void **tmp, t_mparams par,
					int (cmp)(void*, void*))
{
	int		i;
	int		j;
	int		k;
	int		mid;

	mid = (par.right + par.left) / 2;
	i = par.left;
	j = mid + 1;
	k = 0;
	while (i <= mid && j <= par.right)
		if (cmp(array[i], array[j]) <= 0)
			tmp[k++] = array[i++];
		else
			tmp[k++] = array[j++];
	while (i <= mid)
		tmp[k++] = array[i++];
	while (j <= par.right)
		tmp[k++] = array[j++];
	while (--k >= 0)
		array[par.left + k] = tmp[k];
}

static void		ft_sort(void **array, void **tmp, t_mparams par,
					int (cmp)(void*, void*))
{
	int		mid;
	int		tmp_left;
	int		tmp_right;

	if (par.left >= par.right || par.left < 0 || par.right < 0)
		return ;
	mid = (par.right + par.left) / 2;
	tmp_left = par.left;
	tmp_right = par.right;
	par.right = mid;
	ft_sort(array, tmp, par, cmp);
	par.left = mid + 1;
	par.right = tmp_right;
	ft_sort(array, tmp, par, cmp);
	par.left = tmp_left;
	ft_merge(array, tmp, par, cmp);
}

void			ft_mergesort(void **array, int left, int right,
					int (cmp)(void*, void*))
{
	void		**tmp;
	t_mparams	par;

	if (left < 0 || right < 0 || !array || !*array)
		return ;
	if (!(tmp = (void**)malloc((right + 1) * sizeof(void*))))
		return ;
	ft_memcpy(tmp, array, (right + 1) * sizeof(void*));
	par.left = left;
	par.right = right;
	ft_sort(array, tmp, par, cmp);
	free(tmp);
}
