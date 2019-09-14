/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/14 18:39:50 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		main(int argc, char **argv)
{
	int			sock;
	int			port;
	t_env		env;

	(void)env;
	if (argc != 2)
		server_usage(argv[0]);
	if ((port = check_port_range(argv[1])) == -1)
		return (-1);
	if ((sock = create_server(port)) == -1)
		return (-1);
	if ((multi_client_handler(sock)) == -1)
		return (err_msg(-1, "client handler failed"));
	close(sock);
	return (0);
}
