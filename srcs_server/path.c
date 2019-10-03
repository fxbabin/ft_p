/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:14:12 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/03 18:12:43 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		is_dir(char *path)
{
	struct stat		buf;
	int				fd;

	fd = open(path, O_RDONLY);
	if (fstat(fd, &buf) == -1)
		return (-1);
	if (S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

int		is_file(char *path)
{
	struct stat		buf;
	int				fd;

	fd = open(path, O_RDONLY);
	if (fstat(fd, &buf) == -1)
		return (-1);
	if (S_ISREG(buf.st_mode))
		return (1);
	return (0);
}

int		ft_abspath(char *root, char *path, char *buff)
{
	char	**split;
	int		i;
	char	*t;

	i = -1;
	(path[0] == '/')
		? ft_strcpy(buff, root)
		: getcwd(buff, PATH_MAX);
	if (!(split = ft_strsplit(path, '/')))
		return (-1);
	while (split[++i] && (t = ft_strrchr(buff, '/')) != path)
	{
		if (ft_strcmp(split[i], "..") == 0)
			t[(t != buff) ? 0 : 1] = '\0';
		else if (ft_strcmp(split[i], ".") != 0)
		{
			if (((ft_strlen(buff) + 1) >= (PATH_MAX - 1)) || ((ft_strlen(buff)
				+ ft_strlen(split[i])) >= (PATH_MAX - 1)))
				return (-1);
			(buff[1]) ? ft_strcat(buff, "/") : NULL;
			ft_strcat(buff, split[i]);
		}
	}
	free_split(split);
	return (0);
}

int		is_pathvalid(char *root, char *path)
{
	size_t		len;

	len = ft_strlen(root);
	if (ft_strncmp(root, path, len) == 0 && len < ft_strlen(path))
		return (1);
	return (0);
}

void	get_rootpath(char *root, char *path, char *buff)
{
	char	tmp[PATH_MAX];
	size_t	len;

	len = ft_strlen(root);
	ft_abspath(root, path, (char*)(&tmp));
	if (ft_strncmp(root, tmp, len) == 0 && len < ft_strlen(tmp))
		ft_strcpy(buff, ((char*)(&tmp) + len));
	else
		ft_strcpy(buff, "/");
}
