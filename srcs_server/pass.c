/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:44:13 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/14 14:13:42 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		check_user_pass(t_env *env, char *param, char *line)
{
	int		len;
	char	*tmp;

	len = ft_strlen(env->user_name);
	if (ft_strncmp(line, env->user_name, len) == 0
		&& line[len] == ':')
	{
		if (!(tmp = ft_strrchr(line, ':')))
			return (-1);
		if (ft_strcmp(crypt(param, PASS_SALT), tmp + 1) == 0)
			return (1);
		return (-1);
	}
	return (0);
}

int		check_password(t_env *env, char *param)
{
	char	path[PATH_MAX];
	char	*line;
	int		fd;
	int		ret;
	int		r;

	line = NULL;
	path[0] = '\0';
	ft_strcpy(path, env->root_path);
	ft_strcat(path, "/ftp_passwd.txt");
	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
	while ((ret = sget_next_line(fd, &line)) > 0)
	{
		if ((r = check_user_pass(env, param, line)) != 0)
			break ;
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int		add_password(t_env *env, char *param)
{
	char	path[PATH_MAX];
	int		fd;

	(void)param;
	path[0] = '\0';
	ft_strcpy(path, env->root_path);
	ft_strcat(path, "/ftp_passwd.txt");
	if ((fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0755)) == -1)
		return (-1);
	if (!(crypt(param, PASS_SALT)))
		return (-1);
	ft_dprintf(fd, "%s:%s\n", env->user_name, crypt(param, PASS_SALT));
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int		pass(t_env *env, char *param)
{
	char	path[PATH_MAX];
	int		ret;

	if (!param)
		return (err_answer(-1, env->answer, FTP_NOT_LOGGED));
	path[0] = '\0';
	ft_strcpy(path, env->root_path);
	ft_strcat(path, "/ftp_passwd.txt");
	env->is_logged = 0;
	if ((ret = is_file(path)) <= 0)
	{
		if ((ret = open(path, O_CREAT | O_WRONLY, 0644)) == -1 ||
			close(ret) == -1)
			return (err_answer(-1, env->answer, FTP_NOT_LOGGED));
	}
	if ((ret = check_password(env, param)) == -1)
		return (err_answer(-1, env->answer, FTP_NOT_LOGGED));
	if (ret == 0 && add_password(env, param) == -1)
		return (err_answer(-1, env->answer, FTP_NOT_LOGGED));
	env->is_logged = 1;
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_LOGGED_IN]);
	return (0);
}
