/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 16:14:54 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/30 19:32:36 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include <stdio.h>

int		create_data_con(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_printf("Can't connect to '%s': connection error\n", addr);
		return (-1);
	}
	ft_printf("Connected to '%s'\n", addr);
	return (sock);
}

int		port(t_env *env, char *param)
{
	char	**split;
	int		tmp;
	int		i;
	//int		port;

	i = -1;
	if (!(split = ft_strsplit(param, ',')))
		return (err_msg(-1, "strsplit failed"));
	while (split[++i])
	{
		tmp = ft_atoi(split[i]);
		if (tmp < 0 || tmp > 255)
			return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	}
	if (i != 6)
		return (err_answer(-1, env->answer, FTP_SYNT_ERR_PAR));
	env->data_port = ft_atoi(split[4]) * 256 + ft_atoi(split[5]);
	ft_printf("%d\n", env->data_port);
	//send(sock , "toto", 4, 0);
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_CMD_OK]);
	free_split(split);
	return (0);
}
/*
   int		list(t_env *env, char *param)
   {
   (void)param;
   ft_strcpy(env->answer, g_ftp_reply_msg[FTP_FILE_STAT_OK]);
   log_print_user_msg(env->user_name, env->user_id, env->answer);
   send(env->server_sock , env->answer, ft_strlen(env->answer), 0);

   if (!(env->data_sock = create_data_con("127.0.0.1", env->data_port)))
   return (-1);
   send(env->data_sock , "toto\012", 5, 0);
   close(env->data_sock);
   ft_strcpy(env->answer, g_ftp_reply_msg[FTP_DATA_CON_CLOSE]);
//log_print_user_msg(env->user_name, env->user_id, env->answer);
//send(env->server_sock , env->answer, ft_strlen(env->answer), 0);
//ft_strcpy(env->answer, g_ftp_reply_msg[FTP_REQ_ACT_OK]);
return (0);
}*/

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
   int		stdout_fd;
   int		p_fd[2];
   char	buff1[100];

   buff1[0] = '\0';
   stdout_fd = ut_get_stdout_fd(p_fd);
   ft_putstr("hello");
   ut_get_stdout_buffer(100, buff1, stdout_fd, p_fd);
   if (strcmp(buff1, "hello") == 0)
   return (0);
   else
   return (-1);
   }

   int		list_cmd(t_env *env, char *param)
   {
   int		stdout_fd;
   int		p_fd[2];
   char	buff1[100];

   buff1[0] = '\0';
   stdout_fd = ut_get_stdout_fd(p_fd);
   execl("/bin/ls", "ls", "-l", param, NULL);
   ut_get_stdout_buffer(100, buff1, stdout_fd, p_fd);
   send(env->data_sock , (char*)&buff1, ft_strlen((char*)&buff1), 0);
   exit (0);
   }

   static void	signal_handlerr(int signum)
   {
   wait(NULL);
   (void)signum;
//ft_printf("signum: %d\n", signum);
}
*/
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
   }*/

/*
   int		test_putstr_print_ok(void)
   {
   int		stdout_fd;
   int		p_fd[2];
   char	buff1[100];

   buff1[0] = '\0';
   stdout_fd = ut_get_stdout_fd(p_fd);
   ft_putstr("hello");
   ut_get_stdout_buffer(100, buff1, stdout_fd, p_fd);
   if (strcmp(buff1, "hello") == 0)
   return (0);
   else
   return (-1);
   }*/
/*
   static int	child_list(t_env *env, char *param)
   {
//int		stdout_fd;
//int		p_fd[2];
//char	buff1[100];

if (!(env->data_sock = create_data_con("127.0.0.1", env->data_port)))
exit (-1);
dup2(env->data_sock, STDOUT_FILENO );
(void)param;

//buff1[0] = 0;
stdout_fd = ut_get_stdout_fd(p_fd);
ft_putstr("toto");
ut_get_stdout_buffer(100, buff1, stdout_fd, p_fd);
ft_printf("%s\n", buff1);


execl("/bin/ls", "ls", "-l", ".", NULL);
fflush(stdout);
close(env->data_sock);
//execl()
//send(env->data_sock, "toto", 4, 0);

ft_printf("2");
if (dup2(env->data_sock, STDOUT_FILENO) < 0)
{
close(env->data_sock);
exit(-1);
}
ft_printf("2");
ft_printf("\n");
exit(0);
}*/
/*
   static void parent_list(int signum)
   {
   (void)signum;
   wait(NULL);
   }*/


int		list(t_env *env, char *param)
{
	char	abspath[PATH_MAX];
	char	path[PATH_MAX];

	//int		stdout_fd;
	//int		p_fd[2];
	//char	buffer[4096];
	pid_t	pid;

	if (!param)
		ft_strcpy((char*)&abspath, getcwd(path, PATH_MAX));
	param = (char*)&abspath;
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_FILE_STAT_OK]);
	log_print_user_msg(env->user_name, env->user_id, env->answer);
	send(env->server_sock , env->answer, ft_strlen(env->answer), 0);

	if (!(env->data_sock = create_data_con("127.0.0.1", env->data_port)))
		exit (-1);



	pid=fork();

	if(pid < 0)
		printf("Couldn't fork");
	else if (pid == 0)
	{
		int mypipe[2];
		pipe(mypipe);
		int dupstdout= dup2(env->data_sock, STDOUT_FILENO);
		execl("/bin/ls", "/bin/ls", "-l", (char *)0);
		//fflush(stdout);
		close(dupstdout);
		//dup2(env->data_sock, STDOUT_FILENO);
		//dup2(STDOUT_FILENO, env->data_sock);
		//send(env->data_sock, "toto", 4, 0);
		//ft_dprintf(env->data_sock, "toto\n");
		exit(0);
		//fflush(stdout);
		//printf("Couldn't exec");
		//exit(1);
	}
	else
	{
		close(env->data_sock);
		wait(NULL);
	}

	int pipefd[2];
	pipe(pipefd);

	if (fork() == 0)
	{
		close(pipefd[0]);    // close reading end in the child

		dup2(pipefd[1], 1);  // send stdout to the pipe
		dup2(pipefd[1], 2);  // send stderr to the pipe

		close(pipefd[1]);    // this descriptor is no longer needed

		exec(...);
	}
	else
	{
		// parent

		char buffer[1024];

		close(pipefd[1]);  // close the write end of the pipe in the parent

		while (read(pipefd[0], buffer, sizeof(buffer)) != 0)
		{
		}
	}
	/*
	   static void execute_cmd(int fd, char *cmd, char **params) {
	   pid_t cid;
	   size_t i = 0, c = 0;

	   cid = fork();

	   if(cid == 0) {
	   close(STDOUT_FILENO);
	   dup2(fd, STDOUT_FILENO);

	   if(execvp(cmd, params) < 0) {
	   fprintf(stderr, "Could not execute \"%s\": %d\n", cmd, errno);
	   exit(1);
	   }
	   } else {
	   close(fd);
	   waitpid(cid, NULL, 0);
	   exit(1);
	   }
	   }

*/





	//if (is_dir(param) == 1 || is_file(param) == 1)
	/*pid = fork();
	  if (pid < 0)
	  return (err_msg(-1, "client fork failed"));
	  else if (pid == 0)
	  {
	  child_list(env, param);*/
	//buffer[0] = 0;
	/*ut_get_stdout_fd()
	  while ((dup2(filedes[1], STDOUT_FILENO) == -1) && (errno == EINTR)) {}
	  close(filedes[1]);
	  close(filedes[0]);
	  execl("/bin/ls", "ls", "-l", ".", NULL);
	//execl(cmdpath, cmdname, (char*)0);
	perror("execl");
	_exit(1);*/
	//exit(0);
	/*	}
		else
		{
		signal(SIGCHLD, parent_list);
	//signal(SIGCHLD, signal_handlerr);
	}
	(void)param;

	close(env->data_sock);*/
	ft_strcpy(env->answer, g_ftp_reply_msg[FTP_DATA_CON_CLOSE]);
	//log_print_user_msg(env->user_name, env->user_id, env->answer);
	//send(env->server_sock , env->answer, ft_strlen(env->answer), 0);
	//ft_strcpy(env->answer, g_ftp_reply_msg[FTP_REQ_ACT_OK]);
	return (0);
}
