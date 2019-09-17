/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/17 19:06:50 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_p.h"

int		main(int argc, char **argv)
{
	int			sock;
	int			port;
	t_env		env;

	if (argc != 2)
		server_usage(argv[0]);
	if ((port = check_port_range(argv[1])) == -1)
		return (-1);
	if ((sock = create_server(port)) == -1)
		return (-1);
	init_server_file_system(&env);
	init_cmd_hash((t_hash_list*)&(env.hash));
	//void	(*func)(void);
	//if (!(func = hash_get_val((t_hash_list*)&(env.hash), "USER", hash_strcmp)))
	//	return (-1);
	//func();
	if ((multi_client_handler(&env, sock)) == -1)
		return (err_msg(-1, "client handler failed"));
	close(sock);
	return (0);
}
