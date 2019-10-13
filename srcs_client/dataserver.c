/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataserver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:33:08 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/13 22:09:40 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int		treat_sock(t_cenv *cenv, int sock, struct addrinfo *res, int *c)
{
	if (sock < 0)
		return (-1);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
		return (-1);
	cenv->data_ipv[0] = c;
	cenv->data_ipv[1] = '\0';
	if (bind(sock, res->ai_addr, res->ai_addrlen) < 0)
		return (-1);
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
		sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (treat_sock(cenv, sock, res, &c) == -1)
		{
			res = res->ai_next;
			continue;
		}
		listen(sock, 42);
		freeaddrinfo(res_init);
		return (sock);
	}
	freeaddrinfo(res_init);
	return (-1);
}

int				get_port_ip(t_cenv *cenv, int sock)
{
	struct sockaddr_in	sin;
	char				myip[16];
	socklen_t			len;
	char				*t;

	len = sizeof(sin);
	if (getsockname(sock, (struct sockaddr *)&sin, &len) == -1)
		return (-1);
	inet_ntop(AF_INET, &sin.sin_addr, myip, sizeof(myip));
	t = ft_itoa(ntohs(sin.sin_port));
	ft_strcpy(cenv->data_port, t);
	ft_strcpy(cenv->data_ip, myip);
	free(t);
	return (0);
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
	(void)ip;
	if ((ret = getaddrinfo(NULL, port, &hints, &res_init)) != 0)
		return (err_msg(-1, "getaddrinfo failed"));
	if ((sock = get_datasock(cenv, res_init)) == -1)
		return (err_msg(-1, "get_sock failed"));
	if (get_port_ip(cenv, sock) == -1)
		return (err_msg(-1, "get_sock failed"));
	return (sock);
}
