/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:17:39 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/28 18:37:18 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		pwd(t_env *env, char *param)
{
	char	path[PATH_MAX];

	(void)param;
	if (getcwd(path, PATH_MAX) == NULL)
		return (err_answer(-1, env->answer, FTP_FILE_NOT_AVAIL));
	ft_strcpy(env->answer, "257 \"");
	ft_strcat(env->answer, path);
	ft_strcat(env->answer, "\" is current directory.\n");
	return (0);
}
