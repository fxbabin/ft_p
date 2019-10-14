/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 12:05:06 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/14 14:28:36 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				child_list(t_env *env, char *param)
{
	if (dup2(env->data_sock, STDOUT_FILENO) < 0)
	{
		close(env->data_sock);
		exit(-1);
	}
	if (execl("/bin/ls", "/bin/ls", "-l", param, (char *)0) < 0)
	{
		close(env->data_sock);
		exit(-1);
	}
	close(env->data_sock);
	exit(0);
}

int				fork_list(t_env *env, char *param)
{
	int		pid;

	pid = fork();
	if (pid < 0)
		return (err_msg(-1, "fork failed"));
	else if (pid == 0)
		child_list(env, param);
	else
	{
		close(env->data_sock);
		wait(NULL);
	}
	return (0);
}

int				list(t_env *env, char *param)
{
	char	abspath[PATH_MAX];
	char	path[PATH_MAX];

	abspath[0] = 0;
	if (!param)
		ft_strcpy((char*)&abspath, getcwd(path, PATH_MAX));
	else
		ft_servtoreal(env->user_path, param, (char*)&abspath);
	if (!is_pathvalid(env->user_path, (char*)(&abspath)))
		ft_strcpy((char*)&abspath, env->user_path); 
	param = (char*)&abspath;
	if ((env->data_sock = create_data_con(env->data_ip, env->data_port)) == -1)
		return (err_answer(-1, env->answer, FTP_DATA_CON_KO));
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_FILE_STAT_OK]);
	log_print_user_msg(env->user_name, env->user_id, env->answer);
	send(env->server_sock, env->answer, ft_strlen(env->answer), 0);
	fork_list(env, param);
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_DATA_CON_CLOSE]);
	return (0);
}
