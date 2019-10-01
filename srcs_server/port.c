/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:14:54 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/01 14:14:02 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		port(t_env *env, char *param)
{
	char	**split;
	int		tmp;
	int		i;
	//int		port;

	i = -1;
	if (!(split = ft_strsplit(param, ',')))
		return (err_msg(-1, "strsplit failed"));
	while (split[++i])
	{
		tmp = ft_atoi(split[i]);
		if (tmp < 0 || tmp > 255)
			return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	}
	if (i != 6)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	env->data_port = ft_atoi(split[4]) * 256 + ft_atoi(split[5]);
	//ft_printf("%d\n", env->data_port);
	//send(sock , "toto", 4, 0);
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_CMD_OK]);
	free_split(split);
	return (0);
}
