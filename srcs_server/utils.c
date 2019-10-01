/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:13:52 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/01 17:27:33 by fbabin           ###   ########.fr       */
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

int		err_answer(int ret, char *answer, int idx)
{
	ft_strcpy(answer, g_ftp_reply_msg[idx]);
	return (ret);
}

int		log_print(void)
{
	time_t		rawtime;
	struct tm	*ptm;

	if ((rawtime = time(NULL)) == -1)
		return (err_msg(-1, "time command failed"));
	if ((ptm = localtime(&rawtime)) == NULL)
		return (err_msg(-1, "localtime command failed"));
	ft_printf("[%04d/%02d/%02d %02d:%02d:%02d] :: ", ptm->tm_year + 1900,
		ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	return (0);
}

int		log_print_user_msg(char *user, int user_id, char *cmd)
{
	if ((log_print()) == -1)
		return (-1);
	ft_printf("%-*s(%d) : %s", USER_NAME_LEN, user, user_id, cmd);
	return (0);
}

void	free_split(char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		ft_memdel((void**)&split[i]);
	ft_memdel((void**)split);
}
