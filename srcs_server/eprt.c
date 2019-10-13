/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eprt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:43:26 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/13 14:41:29 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		eprt(t_env *env, char *param)
{
	char	**split;
	int		i;

	i = -1;
	if (!(split = ft_strsplit(param, '|')))
		return (err_answer(-1, env->answer, FTP_SERV_NOT_AVAIL));
	while (split[++i])
		;
	if (i != 3)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	ft_strcpy(env->data_ip, split[1]);
	ft_strcpy(env->data_port, split[2]);
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_CMD_OK]);
	free_split(split);
	return (0);
}
