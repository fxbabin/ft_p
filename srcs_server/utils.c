/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:13:52 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/14 18:26:21 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		err_msg(int ret, char *msg)
{
	ft_dprintf(2, "%kError%k :: %s\n", LRED, RESET, msg);
	return (ret);
}

void	server_usage(char *prog_name)
{
	ft_printf("Usage: %s <port [1024-65535]>\n", prog_name);
	exit(-1);
}

int		check_port_range(char *port_str)
{
	int		port;

	if (ft_strlen(port_str) > 5)
		return(err_msg(-1, "invalid port range"));
	port = ft_atoi(port_str);
	if (port < 1024 && port > 65535)
		return(err_msg(-1, "invalid port range"));
	return (port);
}
