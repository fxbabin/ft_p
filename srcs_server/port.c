/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:14:54 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/29 21:43:19 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		create_data_con(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_printf("Can't connect to '%s': connection error\n", addr);
		return (-1);
	}
	ft_printf("Connected to '%s'\n", addr);
	return (sock);
}

int		port(t_env *env, char *param)
{
	char	**split;
	int		tmp;
	int		i;
	//int		port;

	i = -1;
	if (!(split = ft_strsplit(param, ',')))
		return (err_msg(-1, "strsplit failed"));
	while (split[++i])
	{
		tmp = ft_atoi(split[i]);
		if (tmp < 0 || tmp > 255)
			return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	}
	if (i != 6)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	env->data_port = ft_atoi(split[4]) * 256 + ft_atoi(split[5]);
	
	//send(sock , "toto", 4, 0);
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_CMD_OK]);
	free_split(split);
	return (0);
}


int		list(t_env *env, char *param)
{
	(void)param;
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_FILE_STAT_OK]);
	send(env->server_sock , env->answer, ft_strlen(env->answer), 0);
	
	if (!(env->data_sock = create_data_con("127.0.0.1", env->data_port)))
		return (-1);
	send(env->data_sock , "-rw-------  1 peter         848 Dec 14 11:22 00README.txt\015\012\n", ft_strlen("-rw-------  1 peter         848 Dec 14 11:22 00README.txt"), 0);
	close(env->data_sock);
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_DATA_CON_CLOSE]);
	return (0);
}
