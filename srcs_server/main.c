/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/14 18:39:50 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_p.h"

# define HASH_TTSIZE 148

void	toto()
{
	ft_printf("dawd\n");
}

void	tato()
{
	ft_printf("dwd\n");
}

/*
static int		hash_func_len(char *str, int len, int hash_tsize)
{
	int		hash;
	int		i;

	i = -1;
	hash = 5381;
	while (++i < len)
		hash = (((hash << 5) + hash) + str[i]) % hash_tsize;
	return (hash % hash_tsize);
}*/

void		init_cmd_hash(t_hash_list *hash)
{
	ft_bzero(hash, (HASH_TTSIZE) * sizeof(t_hash_list));
	hash_add_key_val((t_hash_list*)(hash), "USER", toto, hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "PASS", tato, hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "ACCT", "acct", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "CWD", "cwd", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "CDUP", "cdup", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "REIN", "rein", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "QUIT", "quit", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "PORT", "port", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "PASV", "pasv", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "TYPE", "type", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "MODE", "mode", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "RETR", "retr", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "STOR", "stor", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "STOU", "stou", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "APPE", "appe", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "REST", "rest", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "RNFR", "rnfr", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "RNTO", "rnto", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "ABOR", "abor", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "DELE", "dele", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "RMD", "rmd", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "MKD", "mkd", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "PWD", "pwd", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "LIST", "list", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "NLIST", "nlist", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "SYST", "syst", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "STAT", "stat", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "HELP", "help", hash_strcmp);
	hash_add_key_val((t_hash_list*)(hash), "NOOP", "noob", hash_strcmp);
}

void	parse_input_cmd(t_hash_list *hash, char *input_cmd)
{
	int		cmd_len;
	void	(*func)(void);
	//int		idx;
	char	tmp[6];

	(void)hash;
	cmd_len = ft_strchrindex(input_cmd, ' ');
	if (cmd_len > 5 || cmd_len == -1)
		return ;
	ft_strncpy((char*)(&tmp), input_cmd, cmd_len);
	//tmp[cmd_len] = '\0';
	//ft_printf("%s\n", tmp);
	//idx = hash_func_len(input_cmd, cmd_len, HASH_TTSIZE);
	if (!(func = hash_get_val(hash, (char*)(&tmp), hash_strcmp)))
		return ;
	func();
}

int			main(int argc, char **argv)
{
	//int				sock;i
	//t_hash_list		*hash;
	t_hash_list		hash[HASH_TTSIZE];
	int				port;
	t_env			env;

	(void)env;
	if (argc != 2)
		server_usage(argv[0]);
	if ((port = check_port_range(argv[1])) == -1)
		return (-1);
	//hash = (t_hash_list*)malloc((HASH_TSIZE) * sizeof(t_hash_list));
	init_cmd_hash((t_hash_list*)(&hash));
	parse_input_cmd((t_hash_list*)(&hash), "PASS dd");
	/*int        i;

	i =0;
	while (++i < HASH_TTSIZE)
	{
		if (hash[i].key != NULL)
			ft_printf("%s -> %s\n", hash[i].key, hash_get_val((t_hash_list*)(&hash), hash[i].key, hash_strcmp));
	}*/
	/*
	   if ((sock = create_server(port)) == -1)
	   return (-1);
	   if ((multi_client_handler(sock)) == -1)
	   return (err_msg(-1, "client handler failed"));
	   close(sock);
	 */
	return (0);
}
/*
#include "ft_p.h"

int		main(int argc, char **argv)
{
int			sock;
int			port;
t_env		env;

(void)env;
if (argc != 2)
server_usage(argv[0]);
if ((port = check_port_range(argv[1])) == -1)
return (-1);
if ((sock = create_server(port)) == -1)
return (-1);
if ((multi_client_handler(sock)) == -1)
return (err_msg(-1, "client handler failed"));
close(sock);
return (0);
}*/
