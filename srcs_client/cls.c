/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cls.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:14:42 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/08 23:11:17 by fbabin           ###   ########.fr       */
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
		return (-1);
	while ((r = recv(cs, buff, 128, 0)) > 0)
	{
		buff[r] = 0;
		ft_printf("%s", buff);
	}
	close(cs);
	return (0);
}

int			toto(t_cenv *cenv, char *param, int datasock)
{
	char	buff[128];
	int		ret;

	(void)param;
	get_ipport(cenv, (char*)&buff);
	if ((ret = send(cenv->csock, buff, ft_strlen(buff), 0)) == -1)
		return (err_msg(-1, "can't send port command"));
	if (receive_reply(cenv) == -1)
		return (err_msg(-1, "can't receive port reply"));
	if ((ret = send(cenv->csock, "LIST\n", 5, 0)) == -1)
		return (err_msg(-1, "can't send list command"));
	if (receive_reply(cenv) == -1)
		return (-1);
	if (cls_receive_data(datasock) == -1)
		return (-1);
	if (receive_reply(cenv) == -1)
		return (-1);
	return (0);
}

int		cls(t_cenv *cenv, char *param)
{
	int		datasock;

	(void)param;
	if ((datasock = create_dataserver(cenv, cenv->data_ip, cenv->data_port)) < 0)
		return (err_msg(-1, "can't create datasock"));
	if (toto(cenv, param, datasock) == -1)
	{
		close(datasock);
		return (-1);
	}
	close(datasock);
	return (0);
}
