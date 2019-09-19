/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:13:52 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/19 19:16:01 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		err_msg(int ret, char *msg)
{
	ft_dprintf(2, "%kError%k :: %s\n", LRED, RESET, msg);
	return (ret);
}

void	server_usage(char *prog_name)
{
	ft_printf("Usage: %s <port [1024-65535]>\n", prog_name);
	exit(-1);
}

void	ft_strtoupper(char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
		cmd[i] = ft_toupper(cmd[i]);
}

int		err_answer(int ret, const char **answer, int idx)
{
	*answer = g_ftp_reply_msg[idx];
	return (ret);
}

int		log_print(char *user, int user_id, char *cmd)
{
	time_t		rawtime;
	struct tm	*ptm;	

	if ((rawtime = time(NULL)) == -1)
		return (err_msg(-1, "time command failed"));
	if ((ptm = localtime(&rawtime)) == NULL)
		return (err_msg(-1, "localtime command failed"));
	ft_printf("[%04d/%02d/%02d %02d:%02d:%02d] :: %-*s(%d) : %s", ptm->tm_year + 1900,
		ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec,
		USER_NAME_LEN, user, user_id, cmd);
	return (0);
}
