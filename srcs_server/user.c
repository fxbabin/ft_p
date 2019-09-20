/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:50:25 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/20 11:38:05 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		user(t_env *env, const char **answer, char *param)
{
	int				fd;
	struct stat		st;
	char			path[PATH_MAX];
	char			tmp[PATH_MAX];

	if (chdir(env->root_path) == -1)
		ft_printf("Error\n");
	path[0] = '\0';
	ft_strcpy((char*)(&tmp), "./");
	ft_strcat((char*)(&tmp), param);
	fd = open(path, O_RDONLY);
	if (fstat(fd, &st) == -1)
		mkdir(param, 0755);
	if (chdir((char*)(&tmp)) == -1)
		ft_printf("Error\n");
	path[0] = '\0';
	ft_strcpy(env->user_path, getcwd(path, PATH_MAX));
	env->user_path_len = ft_strlen(env->user_path);
	*answer = g_ftp_reply_msg[FTP_LOGGED_IN];
	return (0);
}
