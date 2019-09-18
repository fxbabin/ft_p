/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/18 18:48:58 by fbabin           ###   ########.fr       */
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

int		process_cmds(const char **answer, char *input_cmd)
{
	char	tmp[CMD_MAX_LEN + 1];
	int		cmd_len;
	char	*cmd_end;
	char	*param_begin;

	cmd_len = ft_strlen(input_cmd);
	ft_printf("'%s' -> ", input_cmd);
	if (cmd_len > INPUT_MAX_LEN)
		return (err_answer(-1, answer, FTP_SYNT_ERR));
	cmd_end = ft_strchr(input_cmd, ' ');
	param_begin = (cmd_end != NULL) ? ft_strrchr(input_cmd, ' ') : NULL;
	if (cmd_end)
	{
		cmd_len = (int)((char*)cmd_end - (char*)input_cmd);
		while (cmd_end != param_begin)
		{
			if (*cmd_end != ' ')
				return (err_answer(-1, answer, FTP_SYNT_ERR_PAR));
			cmd_end += 1;
		}
	}
	if (cmd_len > CMD_MAX_LEN)
		return (err_answer(-1, answer, FTP_SYNT_ERR_UNK_CMD));
	ft_strncpy((char*)(&tmp), input_cmd, cmd_len);
	tmp[cmd_len] = '\0';
	ft_strtoupper(tmp);
	param_begin += (param_begin) ? 1 : 0;
	*answer = g_ftp_reply_msg[FTP_CMD_OK];
	ft_printf("['%s', '%s']\n", tmp, param_begin);
	//cmd_len = ft_strchrindex(input_cmd, ' ');
	//ft_printf("%d\n", cmd_len);
	//if (cmd_len > 5 || cmd_len == -1)
	//	return (-1);
	//ft_strncpy((char*)(&tmp), input_cmd, cmd_len);
	//ft_printf("%s\n", (char*)(&tmp));
	//if (!(func = hash_get_val((t_hash_list*)&(env->hash), (char*)(&tmp), hash_strcmp)))
	//	return (-1);
	//ft_printf("%s\n", hash_get_val((t_hash_list*)&(env->hash), (char*)(&tmp), hash_strcmp));
	//func();
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
	//void	(*func)(void);
	//if (!(func = hash_get_val((t_hash_list*)&(env.hash), "USER", hash_strcmp)))
	//	return (-1);
	//func();
	/*t_key_val k_val[] = {{"USER ", "dd"}, {"PASS ", "pass"}, {"ACCT ", "acct"},
	  {"CWD  ", "cwd"},   {"CDUP ", "cdup"}, {"REIN ", "rein"},
	  {"QUIT", "quit"}, {"PORT ", "port"}, {"PASV ", "pasv"},
	  {"TYPE ", "type"}, {"MODE ", "mode"}, {"RETR ", "retr"},
	  {"STOR ", "stor"}, {"STOU ", "stou"}, {"APPE ", "appe"},
	  {"REST ", "rest"}, {"RNFR ", "rnfr"}, {"RNTO ", "rnto"},
	  {"ABOR", "abor"}, {"DELE ", "dele"}, {"RMD ", "rmd"},
	  {"MKD ", "mkd"},   {"PWD", "pwd"},   {"LIST", "list"},
	  {"NLIST", "nlist"}, {"SYST", "syst"}, {"STAT", "stat"},
	  {"HELP", "help"}, {"NOOP", "noop"}
	  };*/
	/*int i;

	  i = -1;
	  while (++i < (int)(sizeof(k_val) / sizeof(*k_val)))
	  process_cmds(k_val[i].key);
	  */
	const char	*answer;

	answer = NULL;
	process_cmds(&answer, "PwD");
	ft_printf("%s\n", answer);
	process_cmds(&answer, "PwD ");
	ft_printf("%s\n", answer);
	process_cmds(&answer, "PwD      dsdsds");
	ft_printf("%s\n", answer);
	process_cmds(&answer, "PwD toto");
	ft_printf("%s\n", answer);
	process_cmds(&answer, "PwD toto ddd");
	ft_printf("%s\n", answer);
	process_cmds(&answer, "PwDefsf toto");
	ft_printf("%s\n", answer);

	log_print("user", "pwd");
	//ft_printf("'%s'\n", k_val[i].key);

	//if ((multi_client_handler(&env, sock)) == -1)
	//	return (err_msg(-1, "client handler failed"));
	//close(sock);
	return (0);
}
