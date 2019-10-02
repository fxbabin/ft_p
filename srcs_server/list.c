/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 12:05:06 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/02 18:05:20 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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

int				child_list(t_env *env)
{
	if (dup2(env->data_sock, STDOUT_FILENO) < 0)
	{
		close(env->data_sock);
		exit(-1);
	}
	if (execl("/bin/ls", "/bin/ls", "-l", (char *)0) < 0)
	{
		close(env->data_sock);
		exit(-1);
	}
	close(env->data_sock);
	exit(0);
}

int				list(t_env *env, char *param)
{
	char	abspath[PATH_MAX];
	char	path[PATH_MAX];
	pid_t	pid;

	if (!param)
		ft_strcpy((char*)&abspath, getcwd(path, PATH_MAX));
	param = (char*)&abspath;
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_FILE_STAT_OK]);
	log_print_user_msg(env->user_name, env->user_id, env->answer);
	send(env->server_sock, env->answer, ft_strlen(env->answer), 0);
	if (!(env->data_sock = create_data_con("127.0.0.1", env->data_port)))
		exit(-1);
	pid = fork();
	if (pid < 0)
		return (err_msg(-1, "fork failed"));
	else if (pid == 0)
		child_list(env);
	else
	{
		close(env->data_sock);
		wait(NULL);
	}
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_DATA_CON_CLOSE]);
	return (0);
}
