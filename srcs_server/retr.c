/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:38:56 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/13 14:38:42 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	retr_child(t_env *env, char *abspath)
{
	char	buff[2048];
	int		fd;
	int		r;

	if ((fd = open(abspath, O_RDONLY)) == -1)
	{
		close(env->data_sock);
		exit(err_msg(-1, "open failed"));
	}
	while ((r = read(fd, buff, 2048)) > 0)
	{
		buff[r] = '\0';
		send(env->data_sock, (char*)&buff, r, 0);
	}
	if (close(fd) == -1)
	{
		close(env->data_sock);
		exit(err_msg(-1, "close failed"));
	}
	close(env->data_sock);
	exit(0);
}

int		retr(t_env *env, char *param)
{
	char	abspath[PATH_MAX + 1];
	int		pid;

	if (!param || ft_servtoreal(env->user_path, param, (char*)&abspath) == -1)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_PERM));
	if (!(is_pathvalid(env->user_path, (char*)&abspath))
		|| is_file((char*)&abspath) <= 0)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_PERM));
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_FILE_STAT_OK]);
	log_print_user_msg(env->user_name, env->user_id, env->answer);
	send(env->server_sock, env->answer, ft_strlen(env->answer), 0);
	if (!(env->data_sock = create_data_con(env->data_ip, env->data_port)))
		return (err_msg(-1, "could not create data sock"));
	if ((pid = fork()) < 0)
		exit(err_msg(-1, "fork failed"));
	else if (pid == 0)
		retr_child(env, (char*)&abspath);
	else
	{
		close(env->data_sock);
		wait(NULL);
	}
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_DATA_CON_CLOSE]);
	return (0);
}
