/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:19:22 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/19 19:32:10 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	set_userid(t_env *env)
{
	int		i;

	i = -1;
	while (++i < MAX_USERS)
	{
		if (env->users[i] == 0)
		{
			env->users[i] = 1;
			env->user_id = i;
			ft_strcpy(env->user_name, "ano");
			break ;
		}
	}
	if (i == MAX_USERS)
	{
		i = -1;
		while (++i < MAX_USERS)
		{
			if (env->users[i] == 2)
				env->users[i] = 0;
		}
		set_userid(env);
	}
}

void	init_connexion(const char *answer, int cs)
{
	answer = g_ftp_reply_msg[FTP_SERV_RDY];
	send (cs, answer, ft_strlen(answer), 0);
}

void	process_client(t_env *env, int cs)
{
	const char		*answer;
	char			buff[1024];
	int				r;

	(void)env;
	answer = NULL;
	init_connexion(answer, cs);
	while ((r = read(cs, buff, 1023)) > 0)
	{
		if (r >= 0)
		{
			buff[r] = '\0';
			log_print(env->user_name, env->user_id, buff);
			//ft_putstr("\n");
			process_cmds(env, &answer, buff);
			//process_cmds(env, (char*)&answer, "/Users/fbabin/ft_p/ft_p_server_root/toot");
			//process_cmds(env,(char*)&answer, buff);
			//ft_printf("'%s' || %d\n", answer, ft_strlen((char*)&answer));
			//answer = g_ftp_reply_msg[FTP_LOGGED_IN];
			log_print(env->user_name, env->user_id, (char*)answer);
			send (cs, answer, ft_strlen((char*)answer), 0);
			// write (cs, answer, ft_strlen(answer));
		}
	}
	exit(0);
}

void	signal_handler(int signum)
{
	wait(NULL);
	ft_printf("signum: %d\n", signum);
}

int		multi_client_handler(t_env *env, int sock)
{
	unsigned int			cslen;
	struct sockaddr_in		csin;
	int						pid;
	int						cs;

	ft_bzero((char*)&(env->users), MAX_USERS);
	//init_cmd_hash((t_hash_list*)&(env->hash));
	while ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)))
	{
		set_userid(env);
		pid = fork();
		if (pid < 0)
			return (err_msg(-1, "client fork failed"));
		else if (pid == 0)
			process_client(env, cs);
		else
		{
			signal(SIGCHLD, signal_handler);
			continue ;
		}
		env->users[env->user_id] = 2;
		close(cs);
	}
	return (0);
}
