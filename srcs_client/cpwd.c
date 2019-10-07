/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:50:25 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/07 18:06:38 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		cpwd(t_cenv *cenv, char *param)
{
	char	answer[128];
	int		ret;

	(void)param;
	answer[0] = '\0';
	bufferize_cmd((char*)&answer, "PWD", NULL);
	if ((ret = send(cenv->csock, answer, ft_strlen(answer), 0)) == -1)
		return (-1);
	if (receive_reply(cenv) == -1)
		return (-1);
	if (ft_strncmp(cenv->reply, "257", 3) == 0)
		return (0);
	return (-1);
}
