/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dele.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:29:33 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/03 19:40:52 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			child_dele(char *param)
{
	execl("/bin/rm", "rm", "-f", param, NULL);
	exit(0);
}

static void		signal_handler(int signum)
{
	(void)signum;
	wait(NULL);
}

int				dele(t_env *env, char *param)
{
	char	abspath[PATH_MAX];
	int		pid;

	if (!param)
		return (err_answer(-1, env->answer, FTP_SYNT_BAD_SEQ));
	if (ft_abspath(env->user_path, param, (char*)(&abspath)) == -1)
		return (err_answer(-1, env->answer, FTP_SYNT_BAD_SEQ));
	if (!is_pathvalid(env->user_path, (char*)(&abspath)))
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	if (is_file((char*)(&abspath)) <= 0)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	if ((pid = fork()) < 0)
		return (err_msg(-1, "client fork failed"));
	else if (pid == 0)
		child_dele((char*)&abspath);
	else
		signal(SIGCHLD, signal_handler);
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_REQ_ACT_OK]);
	return (0);
}
