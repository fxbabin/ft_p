/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:46:22 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/06 22:13:07 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		client_handler(t_cenv *cenv)
{
	char		*line;

	line = NULL;
	if (receive_reply(cenv) == -1)
		return (-1);
	ft_putstr("ftp> ");
	while ((sget_next_line(0, &line)) > 0)
	{
		if (cenv->csock < 0)
			ft_putstr("Not connected.\n");
		else
		{
			if (process_ccmds(cenv, line) == -1)
				break ;
		}
		free(line);
		ft_putstr("ftp> ");
	}
	free(line);
	return (0);
}
