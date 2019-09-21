/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:50:25 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/21 19:13:35 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		user(t_env *env, const char **answer, char *param)
{
	char	path[PATH_MAX];
	char	tmp[PATH_MAX];
	DIR		*dir;

	if (chdir(env->root_path) == -1)
		return (err_answer(-1, answer, FTP_FILE_NOT_AVAIL));
	path[0] = '\0';
	ft_strcpy((char*)(&tmp), "./");
	ft_strcat((char*)(&tmp), param);
	if ((dir = opendir((char*)(&tmp))))
	{
		if ((closedir(dir)) == -1)
			return (err_msg(-1, "could not close directory"));
	}
	else if (errno == ENOENT)
		mkdir((char*)(&tmp), 0755);
	if (chdir((char*)(&tmp)) == -1)
		return (err_answer(-1, answer, FTP_FILE_NOT_AVAIL));
	path[0] = '\0';
	ft_strcpy(env->user_path, getcwd(path, PATH_MAX));
	ft_strncpy(env->user_name, param, USER_NAME_LEN);
	env->user_path_len = ft_strlen(env->user_path);
	env->is_logged = 1;
	*answer = g_ftp_reply_msg[FTP_LOGGED_IN];
	return (0);
}

//[FTP_NEED_PASS] = "331 User name okay, need password.\n",
