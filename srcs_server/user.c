/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:50:25 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/27 15:36:02 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static int	is_stralpha(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isalpha(str[i]))
			return (0);
	return (1);
}

int		user(t_env *env, char *param)
{
	char	path[PATH_MAX];
	DIR		*dir;

	if (!param)
		return (err_answer(-1, env->answer, FTP_SYNT_BAD_SEQ));
	if (!is_stralpha(param))
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	if (chdir(env->root_path) == -1)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	if ((dir = opendir(param)) && (closedir(dir)) == -1)
		return (err_msg(-1, "could not close directory"));
	else if (errno == ENOENT && (mkdir(param, 0755)) == -1)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	if (chdir(param) == -1)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	path[0] = '\0';
	ft_strcpy(env->user_path, getcwd(path, PATH_MAX));
	ft_strncpy(env->user_name, param, USER_NAME_LEN);
	env->user_path_len = ft_strlen(env->user_path);
	env->is_logged = 1;
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_LOGGED_IN]);
	return (0);
}
