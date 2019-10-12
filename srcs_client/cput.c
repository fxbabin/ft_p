/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cput.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 19:15:13 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/12 19:40:02 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		cput_send_file(int datasock, char *filename)
{
	char	buff[2048];
	int		fd;
	int		r;

	if ((fd = open(filename, O_RDONLY)) == -1)
		exit(err_msg(-1, "open failed"));
	while ((r = read(fd, buff, 2048)) > 0)
	{
		buff[r] = '\0';
		send(datasock, (char*)&buff, r, 0);
	}
	if (close(fd) == -1)
		exit(err_msg(-1, "close failed"));
	exit(0);
}

int		cput_fork(int datasock, char *param)
{
	int		pid;

	if ((pid = fork()) < 0)
		return (-1);
	else if (pid == 0)
	{
		if (cput_send_file(datasock, param) == -1)
			return (-1);
	}
	else
		wait(NULL);
	return (0);
}

int			cput_process(t_cenv *cenv, char *param, int datasock)
{
	char	buff[128];
	int		ret;

	(void)param;
	get_ipport(cenv, (char*)&buff);
	if ((ret = send(cenv->csock, buff, ft_strlen(buff), 0)) == -1)
		return (err_msg(-1, "can't send port command"));
	if (receive_reply(cenv) == -1)
		return (err_msg(-1, "can't receive port reply"));
	bufferize_cmd((char*)&buff, "STOR ", param);
	if ((ret = send(cenv->csock, buff, ft_strlen(buff), 0)) == -1)
		return (err_msg(-1, "can't send stor command"));
	ft_bzero(buff, 128);
	if (receive_reply(cenv) == -1)
		return (err_msg(-1, "can't receive stor reply"));
	if (cput_fork(datasock, param) == -1)
		return (err_msg(-1, "can't receive data"));
	if (receive_reply(cenv) == -1)
		return (err_msg(-1, "can't receive stor end"));
	return (0);
}

int		cput(t_cenv *cenv, char *param)
{
	int		datasock;

	if (!param)
		return (err_msg(-1, "no file given !"));
	if ((datasock = create_dataserver(cenv, cenv->data_ip, "0")) < 0)
		return (err_msg(-1, "can't create datasock"));
	if (cput_process(cenv, param, datasock) == -1)
	{
		close(datasock);
		return (-1);
	}
	close(datasock);
	return (0);
}
