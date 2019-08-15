/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 22:20:10 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 01:11:51 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"
#include "utils.h"

long		ft_atol(const char *str)
{
	int					sign;
	long				a;

	a = 0;
	while (ft_isspace(*str))
		str++;
	sign = (*str == '-') ? -1 : 1;
	str += (*str == '-' || *str == '+') ? 1 : 0;
	while (*str && ft_isdigit(*str))
		a = (a * 10) + (*(str++) - '0');
	return (sign * a);
}
