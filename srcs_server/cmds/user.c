/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:50:25 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/19 19:51:06 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		user_func(t_env *env, const char **answer, char *param)
{
	int				fd;
	struct stat		st;
	char			path[PATH_MAX];

	if (!param)
		return (err_answer(-1, answer, FTP_SYNT_ERR_BAD_SEQ));
	ft_strcpy((char*)(&path), ROOT_DIR);
	ft_strcat((char*)(&path), param);
	fd = open(path, O_RDONLY);
	if (fstat(fd, &st) == -1)
		mkdir(path, 0755);
	if (close(fd) == -1)
		return (err_answer(-1, answer, FTP_FILE_NOT_AVAIL));
	if (chdir(path) == -1)
		return (err_answer(-1, answer, FTP_FILE_NOT_AVAIL));
	path[0] = '\0';
	env->base_path[0] = '\0';
	ft_strcpy(env->base_path, getcwd(path, PATH_MAX));
	env->base_len = ft_strlen(env->base_path);
	ft_strcpy(env->user_name, "/");
	ft_strcat(env->user_name, param);
}