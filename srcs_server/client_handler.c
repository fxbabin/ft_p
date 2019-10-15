/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:19:22 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/14 23:53:30 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				set_userid(t_env *env)
{
	int		i;

	i = -1;
	while (++i < MAX_USERS)
	{
		if (env->users[i] == 0 || env->users[i] == 2)
		{
			env->users[i] = 1;
			env->user_id = i;
			ft_strcpy(env->user_name, "anonym");
			return (0);
		}
	}
	return (-1);
}

void			init_connexion(char *answer, int cs)
{
	ft_strcpy(answer, g_ftp_reply_msg[FTP_SERV_RDY]);
	send(cs, answer, ft_strlen(answer), 0);
}

void			process_client(t_env *env, int cs)
{
	char	buff[1024];
	int		r;

	init_connexion(env->answer, cs);
	env->server_sock = cs;
	while ((r = read(cs, buff, 1023)) > 0)
	{
		if (r >= 0)
		{
			buff[r] = '\0';
			env->answer[0] = '\0';
			log_print_user_msg(env->user_name, env->user_id, buff);
			process_cmds(env, buff);
			log_print_user_msg(env->user_name, env->user_id, env->answer);
			send(cs, env->answer, ft_strlen(env->answer), 0);
		}
	}
	env->users[env->user_id] = 2;
	close(cs);
	exit(0);
}

static void		signal_handler(int signum)
{
	wait(NULL);
	(void)signum;
}

int				multi_client_handler(t_env *env, int sock)
{
	unsigned int			cslen;
	struct sockaddr_in		csin;
	int						pid;
	int						cs;

	ft_bzero((char*)&(env->users), MAX_USERS);
	env->user_id = -1;
	log_print();
	ft_printf("INFO : Server ready !\n");
	while ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)))
	{
		if (set_userid(env) == -1 && close(cs))
			continue ;
		pid = fork();
		if (pid < 0)
			return (err_msg(-1, "client fork failed"));
		else if (pid == 0)
			process_client(env, cs);
		else
			signal(SIGCHLD, signal_handler);
	}
	return (0);
}
