/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/05 16:25:12 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void    server_usage(char *prog_name)
{
	ft_printf("Usage: %s <port [1024-65535]>\n", prog_name);
	exit(-1);
}

/*
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
   }*/


static int		create_client(char *addr, char *port)
{
	struct addrinfo hints, *res, *res0;
	int error;
	int s;
	const char *cause = NULL;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	error = getaddrinfo(addr, port, &hints, &res0);
	if (error) {
		;
		//errx(1, "%s", gai_strerror(error));
		/*NOTREACHED*/
	}
	s = -1;
	for (res = res0; res; res = res->ai_next) {
		s = socket(res->ai_family, res->ai_socktype,
				res->ai_protocol);
		if (s < 0) {
			cause = "socket";
			continue;
		}
		if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
			cause = "connect";
			close(s);
			s = -1;
			continue;
		}
		break;  /* okay we got one */
	}
	if (s < 0) {
		;
		//err(1, "%s", cause);
		/*NOTREACHED*/
	}
	freeaddrinfo(res0);
	return (s);
}


int		main(int argc, char **argv)
{
	int						port;
	int						sock;

	if (argc != 3)
		server_usage(argv[0]);
	if ((port = check_port_range(argv[2])) == -1)
		return (-1);

	sock = create_client(argv[1], argv[2]);
	char		*line;
	char		server_reply[2000];
	int			r;

	line = NULL;
	//cs = accept(sock, (struct sockaddr*)&csin, &cslen);

	if((r = recv(sock, server_reply , 2000 , 0)) < 0)
		ft_putstr("recv failed\n");
	server_reply[r] = '\0';
	ft_printf("%s", server_reply);
	ft_putstr("ftp>");
	while ((sget_next_line(0, &line)) > 0)
	{
		//server_reply[0] = '\0';
		//write(sock, line, ft_strlen(line));
		if (sock < 0)
			ft_putstr("Not connected.\n");
		else
		{
			if (line[0] == 0)
			{
				free(line);
				ft_putstr("ftp>");
				continue ;
			}

			//ft_printf("'%s'\n", line);
			ft_strcpy((char*)(&server_reply), line);
			ft_strcat((char*)(&server_reply), "\n");
			if( send(sock , (char*)(&server_reply), strlen((char*)(&server_reply)) , 0) < 0)
				ft_putstr("Send failed\n");
			if((r = recv(sock, server_reply , 2000 , 0)) < 0)
				ft_putstr("recv failed\n");
			server_reply[r] = '\0';
			ft_printf("%s", server_reply);
			if (ft_strncmp(server_reply, "221", 3) == 0)
			{
				free(line);
				close(sock);
				return (0);
			}
			ft_strclr((char*)&server_reply);
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
		ft_putstr("ftp>");
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
