/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/18 20:10:14 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_p.h"

// cmd len
//

void	ft_strtoupper(char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
		cmd[i] = ft_toupper(cmd[i]);
}

int		err_answer(int ret, const char **answer, int idx)
{
	*answer = g_ftp_reply_msg[idx];
	return (ret);
}

int		run_func(t_env *env, const char **answer, char *cmd, char *param)
{
	int		(*func)(t_env*, const char**, char*);

	if (!(func = hash_get_val((t_hash_list*)&(env->hash), cmd, hash_strcmp)))
		return (err_answer(-1, answer, FTP_SYNT_ERR_UNK_CMD));
	func(env, answer, param);
	return (0);
}

int		check_cmds(const char **answer, char *input_cmd, char *cmd_end, char *param)
{
	int		cmd_len;

	cmd_len = ft_strlen(input_cmd);
	if (cmd_end)
	{
		cmd_len = (int)((char*)cmd_end - (char*)input_cmd);
		while (cmd_end != param)
		{
			if (*cmd_end != ' ')
				return (err_answer(-1, answer, FTP_SYNT_ERR_PAR));
			cmd_end += 1;
		}
	}
	if (cmd_len > CMD_MAX_LEN)
		return (err_answer(-1, answer, FTP_SYNT_ERR));
	return (cmd_len);
}

int		process_cmds(t_env *env, const char **answer, char *input_cmd)
{
	char	tmp[CMD_MAX_LEN + 1];
	int		cmd_len;
	char	*cmd_end;
	char	*param;

	cmd_len = ft_strlen(input_cmd);
	ft_printf("'%s' -> ", input_cmd);
	if (cmd_len > INPUT_MAX_LEN)
		return (err_answer(-1, answer, FTP_SYNT_ERR));
	cmd_end = ft_strchr(input_cmd, ' ');
	param = (cmd_end != NULL) ? ft_strrchr(input_cmd, ' ') : NULL;
	if ((cmd_len = check_cmds(answer, input_cmd, cmd_end, param)) == -1)
		return (-1);
	ft_strncpy((char*)(&tmp), input_cmd, cmd_len);
	tmp[cmd_len] = '\0';
	ft_strtoupper(tmp);
	param += (param) ? 1 : 0;
	run_func(env, answer, (char*)(&tmp), param);
	return (0);
}

int		main(int argc, char **argv)
{
	int			sock;
	int			port;
	t_env		env;

	if (argc != 2)
		server_usage(argv[0]);
	if ((port = check_port_range(argv[1])) == -1)
		return (-1);
	if ((sock = create_server(port)) == -1)
		return (-1);
	init_server_file_system(&env);
	init_cmd_hash((t_hash_list*)&(env.hash));
	const char	*answer;

	answer = NULL;
	process_cmds(&env, &answer, "PwD");
	ft_printf("%s\n", answer);
	process_cmds(&env, &answer, "PwD ");
	ft_printf("%s\n", answer);
	process_cmds(&env, &answer, "PwD      dsdsds");
	ft_printf("%s\n", answer);
	process_cmds(&env, &answer, "PwD toto");
	ft_printf("%s\n", answer);
	process_cmds(&env, &answer, "PwD toto ddd");
	ft_printf("%s\n", answer);
	process_cmds(&env, &answer, "PwDefsf toto");
	ft_printf("%s\n", answer);

	log_print("user", "pwd");
	//ft_printf("'%s'\n", k_val[i].key);

	//if ((multi_client_handler(&env, sock)) == -1)
	//	return (err_msg(-1, "client handler failed"));
	//close(sock);
	return (0);
}
