/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:16:12 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/14 14:27:22 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		cuser(t_cenv *cenv, char *param)
{
	char	answer[128];
	char	*tmp;
	int		ret;

	answer[0] = '\0';
	bufferize_cmd((char*)&answer, "USER ", param);
	if ((ret = send(cenv->csock, answer, ft_strlen(answer), 0)) == -1)
		return (-1);
	if (receive_reply(cenv) == -1)
		return (-1);
	if (ft_strncmp(cenv->reply, "331", 3) != 0)
		return (-1);
	if ((tmp = getpass("password : ")) == NULL)
		return (-1);
	answer[0] = '\0';
	bufferize_cmd((char*)&answer, "PASS ", tmp);
	free(tmp);
	if ((ret = send(cenv->csock, answer, ft_strlen(answer), 0)) == -1)
		return (-1);
	if (receive_reply(cenv) == -1)
		return (-1);
	return (0);
}
