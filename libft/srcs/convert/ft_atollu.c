/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atollu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:25:38 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 01:13:56 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"
#include "utils.h"

unsigned long long		ft_atollu(const char *str)
{
	int						sign;
	unsigned long long		a;

	a = 0;
	while (ft_isspace(*str))
		str++;
	sign = (*str == '-') ? -1 : 1;
	str += (*str == '-' || *str == '+') ? 1 : 0;
	while (*str && ft_isdigit(*str))
		a = (a * 10) + (*(str++) - '0');
	return (sign * a);
}
