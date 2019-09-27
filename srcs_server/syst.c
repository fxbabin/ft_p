/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:24:38 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/27 18:18:16 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <sys/utsname.h>

int		syst(t_env *env, char *param)
{
	struct utsname details;

	(void)param;
	if (uname(&details) == 0)
	{
		ft_strcpy(env->answer, "215 ");
		ft_strcat(env->answer, details.sysname);
		ft_strcat(env->answer, "\n");
	}
	return (0);
}
