/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:56:45 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/25 19:47:53 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			init_cmd_hash(t_hash_list *hash)
{
	int		i;

	i = -1;
	ft_bzero(hash, (HASH_SIZE) * sizeof(t_hash_list));
	t_key_val k_val[] = {{"USER", user}, {"PASS", NULL}, {"ACCT", NULL},
						 {"CWD", NULL},   {"CDUP", NULL}, {"REIN", NULL},
						 {"QUIT", NULL}, {"PORT", NULL}, {"PASV", NULL},
						 {"TYPE", NULL}, {"MODE", NULL}, {"RETR", NULL},
						 {"STOR", NULL}, {"STOU", NULL}, {"APPE", NULL},
						 {"REST", NULL}, {"RNFR", NULL}, {"RNTO", NULL},
						 {"ABOR", NULL}, {"DELE", NULL}, {"RMD", rmd},
						 {"MKD", mkd},   {"PWD", NULL},   {"LIST", NULL},
						 {"NLIST", NULL}, {"SYST", NULL}, {"STAT", NULL},
						 {"HELP", NULL}, {"NOOP", noop}
	};
	while (++i < (int)(sizeof(k_val) / sizeof(*k_val)))
		hash_add_key_val(hash, k_val[i].key, k_val[i].val, hash_strcmp);
}

static int		run_func(t_env *env, const char **answer, char *cmd,
							char *param)
{
	int		(*func)(t_env*, const char**, char*);

	env->answer[0] = '\0';
	if (env->is_logged == 0 && ft_strcmp(cmd, "USER") != 0)
		return (err_answer(-1, answer, FTP_NOT_LOGGED));
	if (!(func = hash_get_val((t_hash_list*)&(env->hash), cmd, hash_strcmp)))
		return (err_answer(-1, answer, FTP_SYNT_ERR_UNK_CMD));
	func(env, answer, param);
	return (0);
}

static int		check_cmds(const char **answer, char *input_cmd,
							char *cmd_end, char *param)
{
	int		cmd_len;

	cmd_len = ft_strlen(input_cmd);
	if (cmd_end)
	{
		cmd_len = (int)((char*)cmd_end - (char*)input_cmd);
		while (cmd_end != param)
		{
			ft_printf("'%c'\n", *cmd_end);
			if (*cmd_end != ' ')
			{
				err_answer(-1, &(*answer), FTP_SYNT_ERR_PAR);
				ft_printf("%s\n", *answer);
				return (err_answer(-1, &(*answer), FTP_SYNT_ERR_PAR));
			}
			cmd_end += 1;
		}
	}
	if (cmd_len > CMD_MAX_LEN)
		return (err_answer(-1, answer, FTP_SYNT_ERR));
	return (cmd_len);
}

int		check_param_chars(char *param)
{
	int		i;

	i = -1;
	while(param[++i])
	{
		if (!ft_isalpha(param[i]) && param[i] != '.' && param[i] != '/')
			return (-1);
	}
	return (0);
}

int				process_cmds(t_env *env, char *input_cmd)
{
	char	tmp[CMD_MAX_LEN + 1];
	int		cmd_len;
	char	*cmd_end;
	char	*param;

	*answer = NULL;
	cmd_len = ft_strlen(input_cmd);
	//input_cmd[cmd_len] = '\0';
	//ft_printf("'%s' -> ", input_cmd);
	if (cmd_len > INPUT_MAX_LEN)
		return (err_answer(-1, answer, FTP_SYNT_ERR));


	cmd_end = ft_strchr(input_cmd, ' ');
	param = (cmd_end != NULL) ? ft_strrchr(input_cmd, ' ') : NULL;
	if ((cmd_len = check_cmds(answer, input_cmd, cmd_end, param)) == -1)
		return (err_answer(-1, answer, FTP_SYNT_ERR_PAR));
	ft_strncpy((char*)(&tmp), input_cmd, cmd_len);
	tmp[cmd_len] = '\0';
	ft_strtoupper(tmp);
	param += (param) ? 1 : 0;
	env->answer[0] = '\0';
	
	if (check_param_chars(param) == -1)
		return (err_answer(-1, answer, FTP_SYNT_ERR_PAR));

	//ft_strncpy(param, param, ft_strlen(param) - 2);
	//if (param)
	//	param[ft_strlen(param) - 2] = '\0';
	//ft_printf("'%s'\n", param );
	//*answer = "\n";
	//(void)env;
	run_func(env, answer, (char*)(&tmp), param);
	return (0);
}

/*
int				process_cmds(t_env *env, const char **answer, char *input_cmd)
{
	char	tmp[CMD_MAX_LEN + 1];
	int		cmd_len;
	char	*cmd_end;
	char	*param;

	cmd_len = ft_strlen(input_cmd);
	//input_cmd[cmd_len] = '\0';
	//ft_printf("'%s' -> ", input_cmd);
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
	env->buff[0] = '\0';
	
	if (check_param_chars(param) == -1)
		return (err_answer(-1, answer, FTP_SYNT_ERR_PAR));

	//ft_strncpy(param, param, ft_strlen(param) - 2);
	//if (param)
	//	param[ft_strlen(param) - 2] = '\0';
	//ft_printf("'%s'\n", param );
	/answer = g_ftp_reply_msg[FTP_LOGGED_IN];
	//(void)env;
	run_func(env, answer, (char*)(&tmp), param);
	return (0);
}*/
