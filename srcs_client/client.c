/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/08/15 23:40:04 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void	usage(char *prog_name)
{
	ft_printf("Usage: %s <addr> <port [1024-65535]>\n", prog_name);
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

int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_printf("Can't connect to '%s': connection error\n", addr);
		return (-1);
	}
	ft_printf("Connected to '%s'\n", addr);
	return (sock);
}

int		main(int argc, char **argv)
{
	int						port;
	int						sock;

	if (argc != 3)
		usage(argv[0]);
	if ((port = check_port_range(argv[2])) == -1)
		return (-1);
	
	sock = create_client(argv[1], port);
	char		*line;
	char		server_reply[2000];

	line = NULL;
	//cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	ft_printf("ftp>");
	while ((sget_next_line(0, &line)) > 0)
	{
		//write(sock, line, ft_strlen(line));
		if (sock < 0)
			ft_putstr("Not connected.\n");
		else
		{
			if( send(sock , line , strlen(line) , 0) < 0)
				ft_putstr("Send failed\n");
			if( recv(sock, server_reply , 2000 , 0) < 0)
				ft_putstr("recv failed\n");
			ft_printf("%s\n", server_reply);
		/*while ((r = read(cs, buff, 1023)) > 0)
		{
			if (r > 0)
			{
				buff[r] = '\0';
				ft_printf("received (%d bytes): '%s'\n", r, buff);
			}
		}*/
		}
		free(line);
		ft_printf("ftp>");
	}
	free(line);
	close(sock);
/*
	int		ret;
	
	ret = execl("/bin/sh", "-c", "cd", "includes", NULL);
	ft_printf("%d\n", ret);
	//ft_printf("%d\n",chdir(argv[1]));
*/
	return (0);
}
