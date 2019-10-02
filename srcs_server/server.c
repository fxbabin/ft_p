/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:10:08 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/02 15:12:47 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	log_print();
	ft_printf("INFO : Creating server ...\n");
	if ((proto = getprotobyname("tcp")) == 0)
		return (-1);
	sock = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		return (err_msg(-1, "bind error"));
	listen(sock, 42);
	return (sock);
}

int		init_server_file_system(t_env *env)
{
	DIR		*dir;
	char	path[PATH_MAX];

	log_print();
	ft_printf("INFO : Initialing server file system ...\n");
	log_print();
	if ((dir = opendir(ROOT_DIR)))
	{
		ft_printf("INFO : \"%s\" directory already exists.\n", ROOT_DIR);
		if ((closedir(dir)) == -1)
			return (err_msg(-1, "could not close ROOT_DIR"));
	}
	else if (errno == ENOENT)
	{
		mkdir(ROOT_DIR, 0755);
		ft_printf("INFO : \"%s\" directory created.\n", ROOT_DIR);
	}
	if (chdir(ROOT_DIR) == -1)
		return (err_msg(-1, "could not cd to 'ROOT_DIR'"));
	env->root_path[0] = '\0';
	env->is_logged = 0;
	ft_strcpy(env->root_path, getcwd(path, PATH_MAX));
	return (0);
}
