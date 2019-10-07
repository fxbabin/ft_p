/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:44:25 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/07 19:45:33 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		crm(t_cenv *cenv, char *param)
{
	char	answer[128];
	int		ret;

	answer[0] = '\0';
	if (!param)
		return (err_msg(-1, "no path given !"));
	if (ft_strlen(param) >= PATH_MAX)
		return (err_msg(-1, "path too long !"));
	bufferize_cmd((char*)&answer, "DELE ", param);
	if ((ret = send(cenv->csock, answer, ft_strlen(answer), 0)) == -1)
		return (-1);
	if (receive_reply(cenv) == -1)
		return (-1);
	if (ft_strncmp(cenv->reply, "250", 3) == 0)
		return (0);
	return (0);
}
