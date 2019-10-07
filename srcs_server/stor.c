/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stor.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 14:15:21 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/07 18:03:36 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int			get_filename(char *root, char *buff, char *path)
{
	char	*begin;

	begin = ft_strrchr(path, '/');
	if (!begin)
	{
		if (ft_servtoreal(root, path, buff) == -1)
			return (-1);
	}
	else
	{
		if (ft_servtoreal(root, begin + 1, buff) == -1)
			return (-1);
	}
	if (!is_pathvalid(root, buff))
		return (-1);
	return (0);
}

void		child_stor(t_env *env, char *abspath)
{
	int		fd;
	int		r;
	char	server_reply[2000];

	if ((fd = open(abspath, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		close(env->data_sock);
		exit(-1);
	}
	while ((r = recv(env->data_sock, server_reply, 2000, 0)) > 0)
	{
		server_reply[r] = '\0';
		write(fd, server_reply, r);
	}
	if (close(fd) == -1)
	{
		close(env->data_sock);
		exit(-1);
	}
	close(env->data_sock);
	exit(0);
}

int			stor(t_env *env, char *param)
{
	char	abspath[PATH_MAX + 1];
	pid_t	pid;

	if (!param)
		return (-1);
	if (get_filename(env->user_path, (char*)&abspath, param) == -1)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_PERM));
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_FILE_STAT_OK]);
	log_print_user_msg(env->user_name, env->user_id, env->answer);
	send(env->server_sock, env->answer, ft_strlen(env->answer), 0);
	if (!(env->data_sock = create_data_con("127.0.0.1", env->data_port)))
		return (err_msg(-1, "could not create data sock"));
	if ((pid = fork()) < 0)
		return (err_msg(-1, "fork failed"));
	else if (pid == 0)
		child_stor(env, (char*)&abspath);
	else
	{
		close(env->data_sock);
		wait(NULL);
	}
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_DATA_CON_CLOSE]);
	return (0);
}
