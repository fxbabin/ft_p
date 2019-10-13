/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/13 18:44:21 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		get_clientsock(struct addrinfo *res_init)
{
	struct addrinfo		*res;
	int					sock;

	res = res_init;
	while (res)
	{
		sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sock < 0)
		{
			res = res->ai_next;
			continue;
		}
		if (connect(sock, res->ai_addr, res->ai_addrlen) < 0)
		{
			res = res->ai_next;
			continue;
		}
		freeaddrinfo(res_init);
		return (sock);
	}
	freeaddrinfo(res_init);
	return (-1);
}

void	print_cip_port(int sock)
{
	struct sockaddr_in	sin;
	char				myip[16];
	socklen_t			len;

	len = sizeof(sin);
	if (getsockname(sock, (struct sockaddr *)&sin, &len) == -1)
		return ;
	inet_ntop(AF_INET, &sin.sin_addr, myip, sizeof(myip));
	ft_printf("Connected to '%s' with port %d.\n", myip, ntohs(sin.sin_port));
}

int		create_client(char *addr, char *port)
{
	struct addrinfo		hints;
	struct addrinfo		*res_init;
	int					sock;
	int					ret;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_socktype = SOCK_STREAM;
	if ((ret = getaddrinfo(addr, port, &hints, &res_init)) != 0)
		return (err_msg(-1, "getaddrinfo failed"));
	if ((sock = get_clientsock(res_init)) == -1)
		return (err_msg(-1, "get_sock failed"));
	print_cip_port(sock);
	return (sock);
}
