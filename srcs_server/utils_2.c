/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:13:52 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/14 22:55:02 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	ft_strtoupper(char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
		cmd[i] = ft_toupper(cmd[i]);
}

void	free_split(char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split[i]);
	free(split);
}

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
