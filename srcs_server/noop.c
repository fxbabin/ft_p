/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:48:57 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/21 21:12:20 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		noop(t_env *env, const char **answer, char *param)
{
	(void)env;
	(void)param;
	*answer = g_ftp_reply_msg[FTP_CMD_OK];
	return (0);
}
