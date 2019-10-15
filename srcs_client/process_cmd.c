/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:51:02 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/15 14:14:59 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void			init_ccmd_hash(t_hash_list *hash)
{
	int				i;
	const t_key_val k_val[] = {
						{"LS", cls},
						{"PWD", cpwd},
						{"CD", ccd},
						{"MKDIR", cmkdir},
						{"RMDIR", crmdir},
						{"USER", cuser},
						{"QUIT", cquit},
						{"PUT", cput},
						{"GET", cget},
						{"RM", crm},
						{"LLS", clls},
						{"LCD", clcd},
						{"LPWD", clpwd}
	};

	i = -1;
	ft_bzero(hash, (CMD_HASH_SIZE) * sizeof(t_hash_list));
	while (++i < (int)(sizeof(k_val) / sizeof(*k_val)))
		hash_add_key_val(hash, k_val[i].key, k_val[i].val, CMD_HASH_SIZE);
}

static void		*get_hash_val(t_hash_list *hash, char *cmd)
{
	int				hash_idx;
	t_hash_list		*tmp;

	hash_idx = hash_func((char*)cmd, CMD_HASH_SIZE);
	if (hash_idx == -1)
		return (NULL);
	tmp = hash;
	if (&tmp[hash_idx] == NULL || tmp[hash_idx].key == NULL)
		return (NULL);
	return (tmp[hash_idx].value);
}

static int		run_func(t_cenv *cenv, char *cmd, char *param)
{
	int		(*func)(t_cenv*, char*);
	int		ret;

	if (!(func = get_hash_val((t_hash_list*)&(cenv->cmd_hash), cmd)))
		return (err_msg(-1, "can't find function associated with command"));
	if ((ret = func(cenv, param)) == -1)
		return (-1);
	return (0);
}

int				process_ccmds(t_cenv *cenv, char *input_cmd)
{
	char	**split;

	(void)cenv;
	split = NULL;
	if (!(split = ft_split(input_cmd, " \t\r\n")))
		return (err_msg(-1, "split failed"));
	ft_strtoupper(split[0]);
	if (run_func(cenv, split[0], split[1]) == -1)
	{
		free_split(split);
		return (-1);
	}
	free_split(split);
	return (0);
}

int				receive_reply(t_cenv *cenv)
{
	int		r;

	if ((r = recv(cenv->csock, cenv->reply, (PATH_MAX + INPUT_MAX_LEN), 0)) < 0)
		return (err_msg(-1, "recv failed"));
	cenv->reply[r] = '\0';
	ft_printf("%s", cenv->reply);
	if (cenv->reply[0] == '4' || cenv->reply[0] == '5')
		return (-1);
	return (0);
}
