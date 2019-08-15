/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/08/15 16:02:01 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void	usage(char *prog_name)
{
	ft_printf("Usage: %s <port [1024-65535]>\n", prog_name);
	exit(-1);
}

static int		check_port_range(char *port_str)
{
	int		port;

	if (ft_strlenp(port_str) > 5)
		return(err_msg(-1, "invalid port range"));
	port = ft_atoi(port_str);
	if (port < 1024 && port > 65535)
		return(err_msg(-1, "invalid port range"));
	return (port);
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
	if ((port = check_port_range(argv[1])) == -1)
		return (-1);
	
	sock = create_server(port);
	while ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)))
	{
		while ((r = read(cs, buff, 1023)) > 0)
		{
			if (r > 0)
			{
				buff[r] = '\0';
				ft_printf("received (%d bytes): '%s'\n", r, buff);
				send (cs, "toto", 4, 0);
			}
		}
	}
	close(cs);
	close(sock);
/*
	int		ret;
	
	ret = execl("/bin/sh", "-c", "cd", "includes", NULL);
	ft_printf("%d\n", ret);
	//ft_printf("%d\n",chdir(argv[1]));
*/
	return (0);
}
