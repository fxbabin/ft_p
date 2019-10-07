/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cls.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:14:42 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/07 23:58:25 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		get_datasock(t_cenv *cenv, struct addrinfo *res_init)
{
	struct sockaddr_in *addr;
	struct addrinfo		*res;
	int					sock;
	int					i;

	res = res_init;
	i = 2;
	while (res)
	{
		if ((sock = socket(res->ai_family, res->ai_socktype, 
				res->ai_protocol)) < 0 && --i)
		{
			res = res->ai_next;
			continue;
		}
		cenv->data_ipv[0] = i + 48;
		cenv->data_ipv[1] = 0;
		addr = (struct sockaddr_in *)res->ai_addr;
		ft_strcpy(cenv->data_ip, inet_ntoa((struct in_addr)addr->sin_addr));
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

int		create_dataserver(t_cenv *cenv, char *ip, char *port)
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
	ft_strcpy(cenv->tmp_port, port);
	if ((ret = getaddrinfo(ip, port, &hints, &res_init)) != 0)
		return (err_msg(-1, "getaddrinfo failed"));
	if ((sock = get_datasock(cenv, res_init)) == -1)
		return (err_msg(-1, "get_sock failed"));
	return (sock);
}

int		get_port(t_cenv *cenv, char *buff)
{
	char	*tmp;

	(void)buff;
	ft_strcpy(buff, "PORT ");
	if (!(tmp = ft_strreplace(cenv->data_ip, ".", ",")))
		return (-1);
	ft_strcat(buff, tmp);
	ft_strcat(buff, ",");
	free(tmp);
	if (!(tmp = ft_itoa(ft_atoi(cenv->tmp_port) / 256)))
		return (-1);
	ft_strcat(buff, tmp);
	ft_strcat(buff, ",");
	free(tmp);
	if (!(tmp = ft_itoa(ft_atoi(cenv->data_port) % 256)))
		return (-1);
	ft_strcat(buff, tmp);
	ft_strcat(buff, "\n");
	free(tmp);
	ft_printf("> %s\n", buff);
	return (0);
}


void	get_eprt(t_cenv *cenv, char *buff)
{
	ft_strcpy(buff, "EPRT |");
	ft_strcat(buff, cenv->data_ipv);
	ft_strcat(buff, "|");
	ft_strcat(buff, cenv->data_ip);
	ft_strcat(buff, "|");
	ft_strcat(buff, cenv->tmp_port);
	ft_strcat(buff, "|\n");
}


int		cls(t_cenv *cenv, char *param)
{
	char	buff[128];
	int		datasock;
	char	*tmp;
	int ret;

	(void)param;
	if (!(tmp = ft_itoa(53652)))
		return (-1);
	if ((datasock = create_dataserver(cenv, "::1", tmp)) < 0)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	if (cenv->data_ipv[0] == '2')
		get_eprt(cenv, (char*)&buff);
	else
		get_port(cenv, (char*)&buff);
	if ((ret = send(cenv->csock, buff, ft_strlen(buff), 0)) == -1)
		return (-1);
	if (receive_reply(cenv) == -1)
		return (-1);
	if ((ret = send(cenv->csock, "LIST\n", 5, 0)) == -1)
		return (-1);

	if (receive_reply(cenv) == -1)
		return (-1);
	close(datasock);
	return (0);
}
