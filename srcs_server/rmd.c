/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 21:45:19 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/25 14:01:02 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
/*
void	child_rmd(char *param)
{
	execl("/bin/rm", "rm", "-rf", param, NULL);
	exit (0);
}*/
/*
static void	signal_handler(int signum)
{
	(void)signum;
	wait(NULL);
}*/

int		rmd(t_env *env, char *param)
{
	//char	abspath[PATH_MAX];
	DIR		*dir;
	//int		pid;
	
	ft_printf("2\n");
	(void)env;
	if (!param)
		return (err_answer(-1, env->answer, FTP_SYNT_BAD_SEQ));
	/*if (ft_abspath(env->user_path, param, (char*)(&abspath)) == -1)
		return (err_answer(-1, env->answer, FTP_SYNT_BAD_SEQ));
	if (!is_pathvalid(env->user_path, (char*)(&abspath)))
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	*/
	if ((dir = opendir(param)))
	{
		ft_printf("3\n");
		closedir(dir);
		/*pid = fork();
		if (pid < 0)
			return (err_msg(-1, "client fork failed"));
		else if (pid == 0)
			child_rmd(param);
		else
			signal(SIGCHLD, signal_handler);
		*/
	}
	else if (errno == ENOENT)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_REQ_ACT_OK]);
	return (0);
}
