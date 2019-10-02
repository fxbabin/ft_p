/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:42:11 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/02 18:54:27 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		cwd(t_env *env, char *param)
{
	char	abspath[PATH_MAX];

	if (ft_abspath(env->user_path, param, (char*)(&abspath)) == -1)
		return (err_answer(-1, env->answer, FTP_SYNT_BAD_SEQ));
	ft_printf("%s\n", (char*)&abspath);
	if (!is_pathvalid(env->user_path, (char*)(&abspath)))
		ft_strcpy((char*)&abspath, env->user_path);
	if (chdir((char*)&abspath) == -1)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_REQ_ACT_OK]);
	return (0);
}
