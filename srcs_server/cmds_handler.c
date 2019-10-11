/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:56:45 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/11 19:21:04 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			init_cmd_hash(t_hash_list *hash)
{
	int				i;
	const t_key_val k_val[] = {{"USER", user}, {"PASS", pass}, {"ACCT", NULL},
						{"CWD", cwd}, {"CDUP", cdup}, {"REIN", NULL},
						{"QUIT", quit}, {"PORT", port}, {"PASV", NULL},
						{"TYPE", NULL}, {"MODE", NULL}, {"RETR", retr},
						{"STOR", stor}, {"STOU", NULL}, {"APPE", NULL},
						{"REST", NULL}, {"RNFR", NULL}, {"RNTO", NULL},
						{"ABOR", NULL}, {"DELE", dele}, {"RMD", rmd},
						{"MKD", mkd}, {"PWD", pwd}, {"LIST", list},
						{"NLIST", NULL}, {"SYST", syst}, {"STAT", NULL},
						{"HELP", NULL}, {"NOOP", noop}, {"EPRT", eprt}
	};

	i = -1;
	ft_bzero(hash, (HASH_SIZE) * sizeof(t_hash_list));
	while (++i < (int)(sizeof(k_val) / sizeof(*k_val)))
		hash_add_key_val(hash, k_val[i].key, k_val[i].val, HASH_SIZE);
}
static int		hash_func(char *str, int hash_tsize)
{
	int		hash;
	int		i;

	i = -1;
	hash = 5381;
	if (!str)
		return (-1);
	while (str[++i])
		hash = (((hash << 5) + hash) + str[i]) % hash_tsize;
	return (hash % hash_tsize);
}

static void		*ff(t_hash_list* hash, char *cmd)
{
	int				hash_idx;
	t_hash_list		*tmp;

	hash_idx = hash_func((char*)cmd, HASH_SIZE);
	if (hash_idx == -1)
		return (NULL);
	tmp = hash;
	/*while (tmp)
	{
		tmp = tmp->next;
	}*/
	if (&tmp[hash_idx] == NULL || tmp[hash_idx].key == NULL)
		return (NULL);
	return (tmp[hash_idx].value);
}

static int		run_func(t_env *env, char *cmd, char *param)
{
	int		(*func)(t_env*, char*);

	//ft_putstr("1a\n");
	if (env->is_logged == 0 && ((ft_strcmp(cmd, "USER") != 0)
		&& (ft_strcmp(cmd, "QUIT") != 0)))
		return (err_answer(-1, env->answer, FTP_NOT_LOGGED));
	//ft_putstr("1b\n");
	if (!(func = ff((t_hash_list*)&(env->hash), cmd)))
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_UNK_CMD));
	//ft_putstr("1\n");
	if (func(env, param) == -1)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_UNK_CMD));
	//ft_putstr("2\n");
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

	//ft_putstr("a\n");
	if (ft_strlen(input_cmd) > INPUT_MAX_LEN)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR));
	//ft_putstr("b\n");
	if (!(split = ft_split(input_cmd, " \t\r\n")))
		return (err_answer(-1, env->answer, FTP_SYNT_ERR));
	//ft_putstr("c\n");
	i = -1;
	while (split[++i])
		;
	if (i > 2)
	{
		free_split(split);
		return (err_answer(-1, env->answer, FTP_SYNT_BAD_SEQ));
	}
	//ft_putstr("d\n");
	if ((check_cmds(env, split[0], split[1])) == -1)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	ft_strtoupper(split[0]);
	//ft_putstr("e\n");
	run_func(env, split[0], split[1]);
	//ft_putstr("f\n");
	free_split(split);
	//ft_putstr("g\n");
	return (0);
}
