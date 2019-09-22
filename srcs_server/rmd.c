/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 21:45:19 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/22 19:00:24 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	child_rmd(char *param)
{
	execl("/bin/rm", "rm", "-rf", param, NULL);
	exit (0);
}

static void	signal_handler(int signum)
{
	(void)signum;
	wait(NULL);
}

int		rmd(t_env *env, const char **answer, char *param)
{
	DIR		*dir;
	int		pid;

	(void)env;
	if (!param)
		return (err_answer(-1, answer, FTP_SYNT_BAD_SEQ));
	if (ft_strchr(param, '.'))
		return (err_answer(-1, answer, FTP_SYNT_ERR_PAR));
	if ((dir = opendir(param)))
	{
		pid = fork();
		if (pid < 0)
			return (err_msg(-1, "client fork failed"));
		else if (pid == 0)
			child_rmd(param);
		else
			signal(SIGCHLD, signal_handler);
		//ft_printf("here\n");
		//execl("/bin/rm", "rm", "-rf", param, NULL);
	}
	else if (errno == ENOENT)
	{
		//ft_printf("3\n");
		return (err_answer(-1, answer, FTP_FILE_NOT_AVAIL));
		//return (err_msg(-1, "could not close ROOT_DIR"));
	}
	*answer = g_ftp_reply_msg[FTP_REQ_ACT_OK];
	return (0);
}
