/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/08/11 22:59:34 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	usage(char *prog_name)
{
	ft_printf("Usage: %s <port>\n", prog_name);
	exit(-1);
}

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
	{
		ft_printf("bind error\n");
		return (-1);
	}
	listen(sock, 42);
	return (sock);
}

int		main(int argc, char **argv)
{
	int						port;
	int						sock;
	int						cs;
	unsigned int			cslen;
	struct sockaddr_in		csin;
	int						r;
	char					buff[1024];

	if (argc != 2)
		usage(argv[0]);
	port = ft_atoi(argv[1]);
	sock = create_server(port);
	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	while ((r = read(cs, buff, 1023)) > 0)
	{
		if (r > 0)
		{
			buff[r] = '\0';
			ft_printf("received (%d bytes): '%s'\n", r, buff);
		}
	}
	close(cs);
	close(sock);
	return (0);
}
