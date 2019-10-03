/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:56:45 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/01 14:33:08 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			init_cmd_hash(t_hash_list *hash)
{
	int				i;
	const t_key_val k_val[] = {{"USER", user}, {"PASS", NULL}, {"ACCT", NULL},
						{"CWD", cwd}, {"CDUP", cdup}, {"REIN", NULL},
						{"QUIT", quit}, {"PORT", port}, {"PASV", NULL},
						{"TYPE", NULL}, {"MODE", NULL}, {"RETR", NULL},
						{"STOR", stor}, {"STOU", NULL}, {"APPE", NULL},
						{"REST", NULL}, {"RNFR", NULL}, {"RNTO", NULL},
						{"ABOR", NULL}, {"DELE", NULL}, {"RMD", rmd},
						{"MKD", mkd}, {"PWD", pwd}, {"LIST", list},
						{"NLIST", NULL}, {"SYST", syst}, {"STAT", NULL},
						{"HELP", NULL}, {"NOOP", noop}
	};

	i = -1;
	ft_bzero(hash, (HASH_SIZE) * sizeof(t_hash_list));
	while (++i < (int)(sizeof(k_val) / sizeof(*k_val)))
		hash_add_key_val(hash, k_val[i].key, k_val[i].val, hash_strcmp);
}

static int		run_func(t_env *env, char *cmd, char *param)
{
	int		(*func)(t_env*, char*);

	if (env->is_logged == 0 && ft_strcmp(cmd, "USER") != 0)
		return (err_answer(-1, env->answer, FTP_NOT_LOGGED));
	if (!(func = hash_get_val((t_hash_list*)&(env->hash), cmd, hash_strcmp)))
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_UNK_CMD));
	func(env, param);
	return (0);
}

static int		check_cmds(t_env *env, char *cmd, char *param)
{
	if (ft_strlen(cmd) > CMD_MAX_LEN)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR));
	(void)param;
	return (0);
}

int				process_cmds(t_env *env, char *input_cmd)
{
	char	**split;
	int		i;

	if (ft_strlen(input_cmd) > INPUT_MAX_LEN)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR));
	if (!(split = ft_split(input_cmd, " \t\r\n")))
		return (err_answer(-1, env->answer, FTP_SYNT_ERR));
	i = -1;
	while (split[++i])
		;
	if (i > 2)
	{
		free_split(split);
		return (err_answer(-1, env->answer, FTP_SYNT_BAD_SEQ));
	}
	if ((check_cmds(env, split[0], split[1])) == -1)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	ft_strtoupper(split[0]);
	run_func(env, split[0], split[1]);
	free_split(split);
	return (0);
}
