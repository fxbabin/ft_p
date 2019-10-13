/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:50:26 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/13 18:38:09 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		clcd(t_cenv *cenv, char *param)
{
	char	path[PATH_MAX];

	(void)param;
	(void)cenv;
	if (chdir(param) < 0)
		return (err_msg(-1, "lcd failed"));
	ft_printf("succesfully changed local directory to \"%s\"\n",
		getcwd(path, PATH_MAX));
	return (0);
}
