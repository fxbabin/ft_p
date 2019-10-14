/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 15:10:08 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/14 23:20:48 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int	treat_sock(int sock, struct addrinfo *res)
{
	if (sock < 0)
		return (-1);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
		return (-1);
	if (bind(sock, res->ai_addr, res->ai_addrlen) < 0)
		return (-1);
	return (0);
}

int			get_sock(struct addrinfo *res_init)
{
	struct addrinfo		*res;
	int					sock;

	res = res_init;
	while (res)
	{
		sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (treat_sock(sock, res) == -1)
		{
			res = res->ai_next;
			continue ;
		}
		listen(sock, 42);
		freeaddrinfo(res_init);
		return (sock);
	}
	freeaddrinfo(res_init);
	return (-1);
}

void		print_ip_port(int sock)
{
	struct sockaddr_in	sin;
	char				my_ip[16];
	socklen_t			len;

	len = sizeof(sin);
	if (getsockname(sock, (struct sockaddr *)&sin, &len) == -1)
		return ;
	inet_ntop(AF_INET, &sin.sin_addr, my_ip, sizeof(my_ip));
	log_print();
	ft_printf("INFO : socket created on ip : %s and port %d ...\n", my_ip,
	ntohs(sin.sin_port));
}

int			create_server(char *port)
{
	struct addrinfo		hints;
	struct addrinfo		*res_init;
	int					sock;
	int					ret;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((ret = getaddrinfo(NULL, port, &hints, &res_init)) != 0)
		return (err_msg(-1, "getaddrinfo failed"));
	if ((sock = get_sock(res_init)) == -1)
		return (err_msg(-1, "get_sock failed"));
	print_ip_port(sock);
	return (sock);
}

int			init_server_file_system(t_env *env)
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
		if (mkdir(ROOT_DIR, 0755) == -1)
			return (err_msg(-1, "could not create ROOT_DIR"));
		ft_printf("INFO : \"%s\" directory created.\n", ROOT_DIR);
	}
	if (chdir(ROOT_DIR) == -1)
		return (err_msg(-1, "could not cd to 'ROOT_DIR'"));
	env->root_path[0] = '\0';
	env->is_logged = 0;
	ft_strcpy(env->root_path, getcwd(path, PATH_MAX));
	return (0);
}
