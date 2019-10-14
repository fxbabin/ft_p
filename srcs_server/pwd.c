/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:17:39 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/14 23:04:10 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		pwd(t_env *env, char *param)
{
	char	path[PATH_MAX];
	char	serv_path[PATH_MAX];

	(void)param;
	if (getcwd(path, PATH_MAX) == NULL)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	ft_realtoserv(env->user_path, path, (char*)&serv_path);
	ft_strcpy(env->answer, "257 \"");
	ft_strcat(env->answer, serv_path);
	ft_strcat(env->answer, "\" is current directory.\n");
	return (0);
}
