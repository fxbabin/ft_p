/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/08/15 23:57:55 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <sys/stat.h>
static void	usage(char *prog_name)
{
	ft_printf("Usage: %s <port [1024-65535]>\n", prog_name);
	exit(-1);
}

static int		check_port_range(char *port_str)
{
	int		port;

	if (ft_strlenp(port_str) > 5)
		return(err_msg(-1, "invalid port range"));
	port = ft_atoi(port_str);
	if (port < 1024 && port > 65535)
		return(err_msg(-1, "invalid port range"));
	return (port);
}

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_printf("bind error\n");
		return (-1);
	}
	listen(sock, 42);
	return (sock);
}

int		init_server_file_system(t_env *env)
{
	int				fd;
	struct stat		st;
	char			path[PATH_MAX];

	fd = open("ft_p_server_root", O_RDONLY);
	if (fstat(fd, &st) == -1)
		mkdir("ft_p_server_root", 0755);
	if (close(fd) == -1)
		return (err_msg(-1, "close failed on 'ft_p_server_root'"));
	if (chdir("ft_p_server_root") == -1)
		return (err_msg(-1, "could not cd to 'ft_p_server_root'"));
	env->base_path[0] = '\0';
	ft_strcpy(env->base_path, getcwd(path, PATH_MAX));
	env->base_len= ft_strlen(env->base_path);
	return (0);
}

void	get_curr_dir(t_env *env, char *answer_buff)
{
	char	path[PATH_MAX];
	int		path_len;

	//chdir("toot");
	getcwd(path, PATH_MAX);
	path_len = ft_strlen((char*)&path);
	if (path_len <= env->base_len)
		ft_strcpy(answer_buff, "/");
	else
		ft_strcpy(answer_buff, ((char*)&path + env->base_len));
}

void	process_cmds(t_env *env, char *answer_buff, char *str)
{
	(void)str;
	//ft_strcpy(answer_buff, "tato");
	if (ft_strcmp(str, "pwd") == 0)
	{
		get_curr_dir(env, answer_buff);
	}
	else
		ft_strcpy(answer_buff, "Error");
}


int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_env		*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (err_msg(-1, "env malloc failed"));
	init_server_file_system(env);
	

	int						port;
	int						sock;
	int						cs;
	unsigned int			cslen;
	struct sockaddr_in		csin;
	int						r;
	char					buff[1024];
	char					answer[1024];

	if (argc != 2)
		usage(argv[0]);
	if ((port = check_port_range(argv[1])) == -1)
		return (-1);

	sock = create_server(port);
	while ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)))
	{
		while ((r = read(cs, buff, 1023)) > 0)
		{
			if (r > 0)
			{
				buff[r] = '\0';
				
				ft_printf("received (%d bytes): '%s'\n", r, buff);
				
				//process_cmds(env, (char*)&answer, "/Users/fbabin/ft_p/ft_p_server_root/toot");
				process_cmds(env,(char*)&answer, buff);
				send (cs, &answer, ft_strlen((char*)&answer), 0);
			}
		}
	}
	close(cs);
	close(sock);
	return (0);
}
