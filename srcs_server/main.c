/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/13 17:40:26 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int		check_port_range(char *port_str)
{
	int		port;

	if (ft_strlen(port_str) > 5)
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

void	process_client(int cs)
{
	int		r;
	char	buff[1024];
	char	answer[125];

	while ((r = read(cs, buff, 1023)) > 0)
	{
		if (r >= 0)
		{
			buff[r] = '\0';
			ft_printf("received (%d bytes): '%s'\n", r, buff);
			//process_cmds(env, (char*)&answer, "/Users/fbabin/ft_p/ft_p_server_root/toot");
			//process_cmds(env,(char*)&answer, buff);
			//ft_printf("'%s' || %d\n", answer, ft_strlen((char*)&answer));
			answer[0] = '1';
			answer[1] = '\0';
			send (cs, &answer, ft_strlen((char*)&answer), 0);
		}
	}
	exit(0);
}

int		parent_process()
{
	return (0);
}

void	multi_client_handler(int sock)
{
	unsigned int			cslen;
	struct sockaddr_in		csin;
	int						pid;
	int						cs;

	while ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)))
	{
		pid = fork();
		if (pid < 0)
		{
			ft_printf("error in fork\n");
			exit(-1);
		}
		else if (pid == 0)
			process_client(cs);
		else
			continue ;
		close(cs);
		//process_client(cs);
	}
}

int		main(int argc, char **argv)
{
	int			sock;
	int			port;
	t_env		*env;

	if (argc != 2)
		server_usage(argv[0]);
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (err_msg(-1, "env malloc failed"));
	if ((port = check_port_range(argv[1])) == -1)
		return (-1);
	sock = create_server(port);
	multi_client_handler(sock);
	close(sock);
	return (0);
}
