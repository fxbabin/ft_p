/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:14:12 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/14 23:48:50 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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

int		servtoreal_aux(char *param, char *path, char *buff)
{
	char	*ptr;

	if ((ptr = ft_strrchr(buff, '/')) == path)
		return (-1);
	if (ft_strcmp(param, "..") == 0)
		ptr[(ptr != buff) ? 0 : 1] = '\0';
	else if (ft_strcmp(param, ".") != 0)
	{
		if ((ft_strlen(buff) + 1) >= (PATH_MAX - 1))
			return (-1);
		if ((ft_strlen(buff) + ft_strlen(param)) >= (PATH_MAX - 1))
			return (-1);
		if (buff[1])
			ft_strcat(buff, "/");
		ft_strcat(buff, param);
	}
	return (0);
}

int		ft_servtoreal(char *root, char *path, char *buff)
{
	char	**split;
	int		i;

	i = -1;
	(path[0] == '/')
		? ft_strcpy(buff, root)
		: getcwd(buff, PATH_MAX);
	if (!(split = ft_strsplit(path, '/')))
		return (-1);
	while (split[++i])
	{
		if (servtoreal_aux(split[i], path, buff) == -1)
		{
			free_split(split);
			return (-1);
		}
	}
	free_split(split);
	return (0);
}

int		is_pathvalid(char *root, char *path)
{
	size_t		len;

	if (!root || !path)
		return (0);
	len = ft_strlen(root);
	if (ft_strncmp(root, path, len) == 0 && len < ft_strlen(path))
		return (1);
	return (0);
}

void	ft_realtoserv(char *root, char *path, char *buff)
{
	size_t	len;

	len = ft_strlen(root);
	if (ft_strncmp(root, path, len) == 0 && len < ft_strlen(path))
		ft_strcpy(buff, (path + len));
	else
		ft_strcpy(buff, "/");
}
