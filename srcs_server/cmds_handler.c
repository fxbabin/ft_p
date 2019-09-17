/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:56:45 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/17 17:42:18 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fp.h"

void	toto()
{
	ft_printf("dawd\n");
}

void	init_cmd_hash(t_hash_list *hash)
{
	int		i;

	i = -1;
	ft_bzero(hash, (HASH_SIZE) * sizeof(t_hash_list));
	t_key_val k_val[] = {{"USER", toto}, {"PASS", "pass"}, {"ACCT", "acct"},
						 {"CWD", "cwd"},   {"CDUP", "cdup"}, {"REIN", "rein"},
						 {"QUIT", "quit"}, {"PORT", "port"}, {"PASV", "pasv"},
						 {"TYPE", "type"}, {"MODE", "mode"}, {"RETR", "retr"},
						 {"STOR", "stor"}, {"STOU", "stou"}, {"APPE", "appe"},
						 {"REST", "rest"}, {"RNFR", "rnfr"}, {"RNTO", "rnto"},
						 {"ABOR", "abor"}, {"DELE", "dele"}, {"RMD", "rmd"},
						 {"MKD", "mkd"},   {"PWD", "pwd"},   {"LIST", "list"},
						 {"NLIST", "nlist"}, {"SYST", "syst"}, {"STAT", "stat"},
						 {"HELP", "help"}, {"NOOP", "noop"}
	};
	while (++i < (int)(sizeof(k_val) / sizeof(*k_val)))
		hash_add_key_val(hash, k_val[i].key, k_val[i].val, hash_strcmp);
}

int		parse_input_cmd(t_hash_list *hash, char *input_cmd)
{
	void	(*func)(void);
	int		cmd_len;
	char	tmp[6];

	cmd_len = ft_strchrindex(input_cmd, ' ');
	if (cmd_len > 5 || cmd_len == -1)
		return (-1);
	ft_strncpy((char*)(&tmp), input_cmd, cmd_len);
	if (!(func = hash_get_val(hash, (char*)(&tmp), hash_strcmp)))
		return (-1);
	func();
	return (0);
}
