/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:51:02 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/06 22:59:37 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			init_ccmd_hash(t_hash_list *hash)
{
	int				i;
	const t_key_val k_val[] = {
						{"LS", NULL},
						{"PWD", NULL}, 
						{"CD", NULL},
						{"MKDIR", NULL},
						{"RMDIR", NULL},
						{"USER", cuser},
						{"QUIT", cquit},
						{"PUT", NULL},
						{"GET", NULL},
						{"LLS", NULL},
						{"LCD", NULL},
						{"LPWD", NULL}
	};

	i = -1;
	ft_bzero(hash, (CMD_HASH_SIZE) * sizeof(t_hash_list));
	while (++i < (int)(sizeof(k_val) / sizeof(*k_val)))
		hash_add_key_val(hash, k_val[i].key, k_val[i].val, hash_strcmp);
}

static int		run_func(t_cenv *cenv, char *cmd, char *param)
{
	int		(*func)(t_cenv*, char*);
	int		ret;

	if (!(func = hash_get_val((t_hash_list*)&(cenv->cmd_hash), cmd, hash_strcmp)))
		return (err_msg(-1, "can't find function associated with command"));
	if ((ret = func(cenv, param)) == -1)
		return (-1);
	return (0);
}

int				process_ccmds(t_cenv *cenv, char *input_cmd)
{
	char	**split;

	if (!(split = ft_split(input_cmd, " \t\r\n")))
		return (err_msg(-1, "split failed"));
	ft_strtoupper(split[0]);
	if (run_func(cenv, split[0], split[1]) == -1)
		return (err_msg(-1, "run_func failed"));
	free_split(split);
	return (0);
}

int		receive_reply(t_cenv *cenv)
{
	int		r;

	if ((r = recv(cenv->csock, cenv->reply, (PATH_MAX + INPUT_MAX_LEN), 0)) < 0)
		return (err_msg(-1, "recv failed"));
	cenv->reply[r] = '\0';
	ft_printf("%s", cenv->reply);
	return (0);
}
