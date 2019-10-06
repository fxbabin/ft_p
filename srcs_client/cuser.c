/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:16:12 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/06 23:20:24 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	cc(char *buff, char *cmd, char *param)
{
	int		len;

	buff[0] = '\0';
	ft_strcpy(buff, cmd);
	ft_strncat(buff, param, 122);
	len = ft_strlen(buff);
	buff[len] = '\n';
	buff[len + 1] = '\0';
}

int		cuser(t_cenv *cenv, char *param)
{
	char	buff[128];

	(void)cenv;
	(void)param;
	cc((char*)&buff, "USER ", param);
	send (cenv->csock, buff, ft_strlen(buff), 0);
	if (receive_reply(cenv) == -1)
		return (-1);
	ft_printf("password : ");
	char buffer[10];
	read(STDIN_FILENO, buffer, 10);
	
	cc((char*)&buff, "PASS ", buffer);
	if (receive_reply(cenv) == -1)
		return (-1);
	//ft_printf("USER %s\n", param);
	return (0);
}
