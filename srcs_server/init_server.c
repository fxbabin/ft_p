/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:37:55 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/12 15:41:31 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		init_server_file_system(t_env *env)
{
	int				fd;
	struct stat		st;
	char			path[PATH_MAX];

	fd = open("FTP_ROOT", O_RDONLY);
	if (fstat(fd, &st) == -1)
		mkdir("FTP_ROOT", 0755);
	if (close(fd) == -1)
		return (err_msg(-1, "close failed on 'FTP_ROOT'"));
	if (chdir("FTP_ROOT") == -1)
		return (err_msg(-1, "could not cd to 'FTP_ROOT'"));
	env->base_path[0] = '\0';
	ft_strcpy(env->base_path, getcwd(path, PATH_MAX));
	env->base_len = ft_strlen(env->base_path);
	return (0);
}
