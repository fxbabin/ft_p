/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataserver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:33:08 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/11 22:10:50 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int		sock_opt(t_cenv *cenv, int sock, struct addrinfo *res, char c)
{
	struct sockaddr_in *addr;

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int)) < 0)
		return (-1);
	cenv->data_ipv[0] = c;
	cenv->data_ipv[1] = '\0';
	addr = (struct sockaddr_in *)res->ai_addr;
	//ft_strcpy(cenv->data_ip, inet_ntoa((struct in_addr)addr->sin_addr));
	return (0);
}

static int		get_datasock(t_cenv *cenv, struct addrinfo *res_init)
{
	struct addrinfo		*res;
	int					sock;
	char				c;

	res = res_init;
	c = '2';
	while (res)
	{
		if ((sock = socket(res->ai_family, res->ai_socktype,
						res->ai_protocol)) < 0 && --c)
		{
			res = res->ai_next;
			continue;
		}
		if (sock_opt(cenv, sock, res, c) == -1)
		{
			res = res->ai_next;
			continue ;
		}
		if (bind(sock, res->ai_addr, res->ai_addrlen) < 0
				&& (res = res->ai_next))
			continue;
		listen(sock, 42);
		freeaddrinfo(res_init);
		return (sock);
	}
	freeaddrinfo(res_init);
	return (-1);
}

int				create_dataserver(t_cenv *cenv, char *ip, char *port)
{
	struct addrinfo		hints;
	struct addrinfo		*res_init;
	int					sock;
	int					ret;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	ft_strcpy(cenv->tmp_port, port);
	(void)ip;
	if ((ret = getaddrinfo(NULL, port, &hints, &res_init)) != 0)
		return (err_msg(-1, "getaddrinfo failed"));
	if ((sock = get_datasock(cenv, res_init)) == -1)
		return (err_msg(-1, "get_sock failed"));
	return (sock);
}
