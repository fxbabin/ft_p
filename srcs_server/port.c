/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:14:54 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/03 20:11:17 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	get_ip(t_env *env, char **split)
{
	ft_strcpy(env->data_ip, split[0]);
	ft_strcat(env->data_ip, ".");
	ft_strcat(env->data_ip, split[1]);
	ft_strcat(env->data_ip, ".");
	ft_strcat(env->data_ip, split[2]);
	ft_strcat(env->data_ip, ".");
	ft_strcat(env->data_ip, split[3]);
}

int		port(t_env *env, char *param)
{
	char	**split;
	int		tmp;
	int		i;

	i = -1;
	if (!(split = ft_strsplit(param, ',')))
		return (err_msg(-1, "strsplit failed"));
	while (split[++i])
	{
		tmp = ft_atoi(split[i]);
		if (ft_strlen(split[i]) > 3)
			return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
		if (tmp < 0 || tmp > 255)
			return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	}
	if (i != 6)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	get_ip(env, split);
	env->data_port = ft_atoi(split[4]) * 256 + ft_atoi(split[5]);
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_CMD_OK]);
	free_split(split);
	return (0);
}
