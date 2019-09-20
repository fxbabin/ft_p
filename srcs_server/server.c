/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:14:51 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/20 11:38:09 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
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
	int				fd;
	struct stat		st;
	char			path[PATH_MAX];

	fd = open(ROOT_DIR, O_RDONLY);
	if (fstat(fd, &st) == -1)
		mkdir(ROOT_DIR, 0755);
	if (chdir(ROOT_DIR) == -1)
		return (err_msg(-1, "could not cd to 'ROOT_DIR'"));
	env->root_path[0] = '\0';
	ft_strcpy(env->root_path, getcwd(path, PATH_MAX));
	return (0);
}
