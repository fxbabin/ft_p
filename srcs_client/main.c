/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:39:09 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/12 16:36:07 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		main(int argc, char **argv)
{
	t_cenv	cenv;
	int		port;

	if (argc != 3)
		server_usage(argv[0]);
	if ((port = check_port_range(argv[2])) == -1)
		return (-1);
	if ((cenv.csock = create_client(argv[1], argv[2])) == -1)
		return (-1);
	init_ccmd_hash((t_hash_list*)&(cenv.cmd_hash));
	client_handler(&cenv);
	close(cenv.csock);
	return (0);
}
