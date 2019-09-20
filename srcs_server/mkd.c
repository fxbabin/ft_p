/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mkd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:13:44 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/20 12:44:17 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		mkd(t_env *env, const char **answer, char *param)
{
	int				fd;
	struct stat		st;

	fd = open(ROOT_DIR, O_RDONLY);
	if (fstat(fd, &st) == -1)
		mkdir(ROOT_DIR, 0755);
	*answer = g_ftp_reply_msg[FTP_LOGGED_IN];
	return (0);
}
