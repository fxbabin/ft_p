/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:00:18 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/30 19:31:02 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <stdio.h>

int		check_port_range(char *port_str)
{
	int		port;

	if (ft_strlen(port_str) > 5)
		return(err_msg(-1, "invalid port range"));
	port = ft_atoi(port_str);
	return (port);
}

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	execl("/bin/ls", "/bin/ls", "-l", (char *)0);
	/*int			sock;
	int			port;
	t_env		env;

	if (argc != 2)
		server_usage(argv[0]);
	if ((port = check_port_range(argv[1])) == -1)
		return (1);
	if ((sock = create_server(port)) == -1)
		return (-1);
	if ((init_server_file_system(&env)) == -1)
		return (-1);
	init_cmd_hash((t_hash_list*)&(env.hash));
	if ((multi_client_handler(&env, sock)) == -1)
		return (err_msg(-1, "client handler failed"));
	close(sock);
	return (0);*/
}

/*
int		ut_get_stdout_fd(int *p_fd)
{
	int		stdout_fd;

	if (!p_fd)
		exit(-1);
	if ((stdout_fd = dup(STDOUT_FILENO)) < 0)
		exit(-1);
	pipe(p_fd);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	close(p_fd[0]);
	return (stdout_fd);
}

char	*ut_get_stdout_buffer(int buff_size, char *buff_out, int stdout_fd,
		int *p_fd)
{
	int		ret;

	if (!buff_out || !p_fd)
		exit(-1);
	if (stdout_fd < 0)
		exit(-1);
	dup2(stdout_fd, STDOUT_FILENO);
	if ((ret = read(p_fd[0], buff_out, buff_size)) < 0)
		exit(-1);
	buff_out[ret] = '\0';
	close(p_fd[0]);
	close(stdout_fd);
	return (buff_out);
}

int		test_putstr_print_ok(void)
{
	execl("/bin/ls", "/bin/ls", "-l", NULL);
	fflush(stdout);
	return (0);
}

void	parr()
{
	int		status;

	wait(&status);
	printf("%d\n", status);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int		pid;

	pid = fork();
	if (pid == 0)
		test_putstr_print_ok();
	else
		parr();
	printf("done\n");
}*/

