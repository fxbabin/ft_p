/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cls.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:14:42 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/13 14:45:44 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		cls_receive_data(int datasock)
{
	unsigned int			cslen;
	struct sockaddr_in		csin;
	char					buff[128];
	int						cs;
	int						r;

	if ((cs = accept(datasock, (struct sockaddr*)&csin, &cslen)) < 0)
		exit (-1);
	ft_bzero(buff, 128);
	while ((r = recv(cs, buff, 64, 0)) > 0)
	{
		buff[r] = '\0';
		ft_putstr(buff);
	}
	if (close(cs) == -1)
		exit (-1);
	exit (0);
}

int		cls_fork(int datasock)
{
	int		pid;

	if ((pid = fork()) < 0)
		return (-1);
	else if (pid == 0)
		cls_receive_data(datasock);
	else
		wait(NULL);
	return (0);
}

int			cls_process(t_cenv *cenv, char *param, int datasock)
{
	char	buff[128];
	int		ret;

	(void)param;
	get_ipport(cenv, (char*)&buff);
	if ((ret = send(cenv->csock, buff, ft_strlen(buff), 0)) == -1)
		return (err_msg(-1, "can't send port command"));
	if (receive_reply(cenv) == -1)
		return (err_msg(-1, "can't receive port reply"));
	bufferize_cmd((char*)&buff, "LIST ", param);
	if ((ret = send(cenv->csock, buff, ft_strlen(buff), 0)) == -1)
		return (err_msg(-1, "can't send list command"));
	ft_bzero(buff, 128);
	if (receive_reply(cenv) == -1)
		return (err_msg(-1, "can't receive list reply"));
	if (cls_fork(datasock) == -1)
		return (err_msg(-1, "can't receive data"));
	if (receive_reply(cenv) == -1)
		return (err_msg(-1, "can't receive end "));
	return (0);
}

int		cls(t_cenv *cenv, char *param)
{
	int		datasock;

	if ((datasock = create_dataserver(cenv, cenv->data_ip, "0")) < 0)
		return (err_msg(-1, "can't create datasock"));
	if (cls_process(cenv, param, datasock) == -1)
	{
		close(datasock);
		return (-1);
	}
	close(datasock);
	return (0);
}
