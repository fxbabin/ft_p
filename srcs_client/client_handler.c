/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:46:22 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/07 11:56:36 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		client_handler(t_cenv *cenv)
{
	char		buff[128];
	int			ret;

	if (receive_reply(cenv) == -1)
		return (-1);
	ft_putstr("ftp> ");
	buff[0] = '\0';
	while ((ret = read(0, buff, 128)) > 0)
	{
		if (ret == 1)
			;
		else if (cenv->csock < 0)
			ft_putstr("Not connected.\n");
		else
			process_ccmds(cenv, (char*)&buff);
		ft_putstr("ftp> ");
		buff[0] = '\0';
	}
	return (0);
}
