/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:56:45 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/18 19:30:40 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
void	*toto()
{
	ft_printf("dawd\n");
	return (NULL);
}
*/

void	init_cmd_hash(t_hash_list *hash)
{
	int		i;

	i = -1;
	ft_bzero(hash, (HASH_SIZE) * sizeof(t_hash_list));
	t_key_val k_val[] = {{"USER", NULL}, {"PASS", NULL}, {"ACCT", NULL},
						 {"CWD", NULL},   {"CDUP", NULL}, {"REIN", NULL},
						 {"QUIT", NULL}, {"PORT", NULL}, {"PASV", NULL},
						 {"TYPE", NULL}, {"MODE", NULL}, {"RETR", NULL},
						 {"STOR", NULL}, {"STOU", NULL}, {"APPE", NULL},
						 {"REST", NULL}, {"RNFR", NULL}, {"RNTO", NULL},
						 {"ABOR", NULL}, {"DELE", NULL}, {"RMD", NULL},
						 {"MKD", NULL},   {"PWD", NULL},   {"LIST", NULL},
						 {"NLIST", NULL}, {"SYST", NULL}, {"STAT", NULL},
						 {"HELP", NULL}, {"NOOP", NULL}
	};
	while (++i < (int)(sizeof(k_val) / sizeof(*k_val)))
		hash_add_key_val(hash, k_val[i].key, k_val[i].val, hash_strcmp);
}

int		process_cmd(t_env *env, char *input_cmd)
{
	void	(*func)(void);
	int		cmd_len;
	char	tmp[6];

	cmd_len = ft_strchrindex(input_cmd, ' ');
	//ft_printf("%d\n", cmd_len);
	if (cmd_len > 5 || cmd_len == -1)
		return (-1);
	ft_strncpy((char*)(&tmp), input_cmd, cmd_len);
	tmp[cmd_len] = '\0';
	//ft_printf("%s\n", (char*)(&tmp));
	if (!(func = hash_get_val((t_hash_list*)&(env->hash), (char*)(&tmp), hash_strcmp)))
		return (-1);
	//ft_printf("%s\n", hash_get_val((t_hash_list*)&(env->hash), (char*)(&tmp), hash_strcmp));
	func();
	return (0);
}
