/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stor.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 14:15:21 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/01 18:40:21 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <stdio.h>

static int		create_data_con(char *addr, int port)
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

void		get_filename(char *root, char *buff, char *path)
{
	char	*begin;

	//printf("'%s'\n", path);
	begin = ft_strrchr(path, '/');
	if (!begin)
		ft_abspath(root, path, buff);
	else
		ft_abspath(root, begin + 1, buff);
}

int		stor(t_env *env, char *param)
{
	char	abspath[PATH_MAX + 1];
	//char	path[PATH_MAX];
	pid_t	pid;

	if (!param)
		return (-1);
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_FILE_STAT_OK]);
	log_print_user_msg(env->user_name, env->user_id, env->answer);
	send(env->server_sock , env->answer, ft_strlen(env->answer), 0);
	
	get_filename(env->user_path, (char*)&abspath, param);
	//printf("'%s'\n", (char*)&abspath);
	//ft_abspath(env->user_path, param, (char*)&abspath);
	//printf("%s\n", abspath);
	if (!(env->data_sock = create_data_con("127.0.0.1", env->data_port)))
		exit (-1);

	pid = fork();
	if(pid < 0)
		return (err_msg(-1, "fork failed"));
	else if (pid == 0)
	{
		int		fd;
		int		r;
		char	server_reply[2000];
		//char	*tmp;

		if ((fd = open(abspath, O_CREAT | O_WRONLY, 0644)) == -1)
			exit(-1);
		//printf("%s\n", "tot");
		//ft_bzero(server_reply, 2000);
		while ((r = recv(env->data_sock, server_reply , 2000 , 0)) > 0)
		{
			//server_reply[r] = '\0';
			//tmp = ft_strreplace(server_reply, "\r\n", "\n");
			write(fd, server_reply, r);
			//free(tmp);
			//ft_bzero(server_reply, 2000);
			//printf("%s\n", server_reply);
			//ft_printf("toto\n");
			//fflush(stdout);

		}
		if (close(fd) == -1)
			exit (-1);
		close(env->data_sock);
		exit(0);
	}
	else
	{
		close(env->data_sock);
		wait(NULL);
	}
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_DATA_CON_CLOSE]);
	return (0);
}
