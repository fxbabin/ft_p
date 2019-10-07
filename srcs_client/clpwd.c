/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clpwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:46:13 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/07 18:46:55 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		child_clpwd()
{
	if (execl("/bin/pwd", "/bin/pwd", (char *)0) < 0)
		exit(-1);
	exit(0);
}

int		clpwd(t_cenv *cenv, char *param)
{
	int		pid;

	(void)param;
	(void)cenv;
	if ((pid = fork()) < 0)
		return (-1);
	else if (pid == 0)
		child_clpwd();
	else
		wait(NULL);
	return (0);
}
