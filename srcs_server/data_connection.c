/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_connection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:33:56 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/12 19:59:26 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		get_datasock(struct addrinfo *res_init)
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

int		create_data_con(char *addr, char *port)
{
	struct addrinfo		hints;
	struct addrinfo		*res_init;
	int					sock;
	int					ret;

	(void)addr;
	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_socktype = SOCK_STREAM;
	if ((ret = getaddrinfo(NULL, port, &hints, &res_init)) != 0)
		return (err_msg(-1, "getaddrinfo failed"));
	if ((sock = get_datasock(res_init)) == -1)
		return (err_msg(-1, "get_sock failed"));
	struct sockaddr_in sin;
	char	myIP[16];
	socklen_t len = sizeof(sin);
	if (getsockname(sock, (struct sockaddr *)&sin, &len) == -1)
		ft_printf("getsockname\n");
	inet_ntop(AF_INET, &sin.sin_addr, myIP, sizeof(myIP));
	ft_printf("ip %s port %d\n", myIP, ntohs(sin.sin_port));
	return (sock);
}
