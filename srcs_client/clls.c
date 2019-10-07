/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:14:54 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/07 19:12:23 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		child_clls()
{
	if (execl("/bin/ls", "/bin/ls", "-l", (char *)0) < 0)
		exit(-1);
	exit(0);
}

int		clls(t_cenv *cenv, char *param)
{
	int		pid;

	(void)param;
	(void)cenv;
	if ((pid = fork()) < 0)
		return (-1);
	else if (pid == 0)
		child_clls();
	else
		wait(NULL);
	return (0);
}
