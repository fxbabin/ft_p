/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:19:22 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/16 15:52:01 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
* 120 Service ready in nnn minutes
* 220 Service ready for new user
* 421 
*/

const char * const ftp_reply_msg[] = {
	[FTP_CMD_OK] = "200 Command okay.\n",
	[FTP_SERV_RDY] = "220 Service ready for new user.\n",
	[FTP_USER_LOGGED] = "230 User logged in, proceed.\n"
};

void	process_client(int cs)
{
	//char			answer[125];
	const char		*answer;
	char			buff[1024];
	int				r;

	answer = ftp_reply_msg[FTP_SERV_RDY];
	send (cs, answer, ft_strlen(answer), 0);
	while ((r = read(cs, buff, 1023)) > 0)
	{
		if (r >= 0)
		{
			buff[r] = '\0';
			ft_printf("[anonymous] :: '%s'\n", buff);
			//process_cmds(env, (char*)&answer, "/Users/fbabin/ft_p/ft_p_server_root/toot");
			//process_cmds(env,(char*)&answer, buff);
			//ft_printf("'%s' || %d\n", answer, ft_strlen((char*)&answer));
			answer = ftp_reply_msg[FTP_USER_LOGGED];
			ft_printf("[anonymous] > '%s'\n", answer);
			send (cs, answer, ft_strlen((char*)answer), 0);
			// write (cs, answer, ft_strlen(answer));
		}
	}
	exit(0);
}

void	signal_handler(int signum)
{
	wait(NULL);
	ft_printf("signum: %d\n", signum);
}

int		multi_client_handler(int sock)
{
	unsigned int			cslen;
	struct sockaddr_in		csin;
	int						pid;
	int						cs;

	while ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)))
	{
		pid = fork();
		if (pid < 0)
			return (err_msg(-1, "client fork failed"));
		else if (pid == 0)
			process_client(cs);
		else
		{
			signal(SIGCHLD, signal_handler);
			continue ;
		}
		close(cs);
	}
	return (0);
}
