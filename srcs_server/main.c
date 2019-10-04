/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/04 22:45:16 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <stdio.h>

int		check_port_range(char *port_str)
{
	int		port;

	if (ft_strlen(port_str) > 5)
		return (err_msg(-1, "invalid port range"));
	port = ft_atoi(port_str);
	return (port);
}

int		main(int argc, char **argv)
{
	int			sock;
	int			port;
	t_env		env;

	if (argc != 2)
		server_usage(argv[0]);
	if ((port = check_port_range(argv[1])) == -1)
		return (1);
	if ((sock = create_server(argv[1])) == -1)
		return (-1);
	if ((init_server_file_system(&env)) == -1)
		return (-1);
	init_cmd_hash((t_hash_list*)&(env.hash));
	if ((multi_client_handler(&env, sock)) == -1)
		return (err_msg(-1, "client handler failed"));
	close(sock);
	return (0);
}
