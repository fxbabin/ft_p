/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 22:15:35 by fbabin            #+#    #+#             */
/*   Updated: 2019/07/20 15:43:05 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

int				ft_qs_intcmp(void *n1, void *n2)
{
	int		pivot;

	pivot = *((int*)n2);
	return (*((int*)n1) - pivot);
}

int				ft_qs_strcmp(void *s1, void *s2)
{
	const unsigned char		*tmp1;
	const unsigned char		*tmp2;

	tmp1 = (const unsigned char *)s1;
	tmp2 = (const unsigned char *)s2;
	while (*tmp1 || *tmp2)
	{
		if (*tmp1 != *tmp2)
			return (*tmp1 - *tmp2);
		tmp1++;
		tmp2++;
	}
	return (0);
}

void			ft_qs_swap(void **arr, int left, int right)
{
	void	*tmp;

	tmp = arr[left];
	arr[left] = arr[right];
	arr[right] = tmp;
}

static int		ft_partition(void **array, int left, int right,
					int (cmp)(void*, void*))
{
	void	*pivot;

	pivot = array[(left + right) / 2];
	while (left <= right)
	{
		while (cmp(array[left], pivot) < 0)
			left++;
		while (cmp(array[right], pivot) > 0)
			right--;
		if (left <= right)
		{
			ft_qs_swap(array, left, right);
			left++;
			right--;
		}
	}
	return (left);
}

void			ft_quicksort(void **array, int left, int right,
					int (cmp)(void*, void*))
{
	int		index;

	if (left >= right || left < 0 || right < 0 || !array)
		return ;
	index = ft_partition(array, left, right, cmp);
	ft_quicksort(array, left, index - 1, cmp);
	ft_quicksort(array, index, right, cmp);
}
