/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:13:52 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/13 18:48:27 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	server_usage(char *prog_name)
{
	ft_printf("Usage: %s <ip> <port [0-65535]>\n", prog_name);
	exit(-1);
}

int		err_msg(int ret, char *msg)
{
	ft_dprintf(2, "%kError%k :: %s\n", LRED, RESET, msg);
	return (ret);
}

int		check_port_range(char *port_str)
{
	int		port;

	if (ft_strlen(port_str) > 5)
		return (err_msg(-1, "invalid port range"));
	port = ft_atoi(port_str);
	return (port);
}

void	ft_strtoupper(char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
		cmd[i] = ft_toupper(cmd[i]);
}

void	free_split(char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split[i]);
	free(split);
}
