/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdup.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:10:52 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/28 16:21:25 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		cdup(t_env *env, char *param)
{
	(void)param;
	if (chdir(env->user_path) == -1)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_CMD_OK]);
	return (0);
}
