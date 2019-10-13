/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cquit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:12:41 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/13 18:44:45 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				cquit(t_cenv *cenv, char *param)
{
	char	answer[128];
	int		ret;

	(void)param;
	answer[0] = '\0';
	bufferize_cmd((char*)&answer, "QUIT", NULL);
	if ((ret = send(cenv->csock, answer, ft_strlen(answer), 0)) == -1)
		return (-1);
	if (receive_reply(cenv) == -1)
		return (-1);
	if (ft_strncmp(cenv->reply, "221", 3) == 0)
		exit(0);
	return (-1);
}
