/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:02:19 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/03 17:57:38 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# include "libft.h"

# include <stdlib.h>
# include <limits.h>
# include <sys/stat.h>

# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/wait.h>
# include <signal.h>
# include <time.h>
# include <dirent.h>
# include <errno.h>

# define HASH_SIZE		148
# define ROOT_DIR		"./ROOT_DIR"
# define CMD_MAX_LEN	4
# define INPUT_MAX_LEN	128
# define MAX_USERS		128
# define USER_NAME_LEN	6

/*
** -------------------------------- STRUCTURES ---------------------------------
*/

typedef struct		s_env
{
	char			answer[PATH_MAX + INPUT_MAX_LEN];
	char			users[MAX_USERS + 1];
	t_hash_list		hash[HASH_SIZE];
	char			root_path[PATH_MAX];
	int				user_id;
	char			is_logged;
	char			user_name[USER_NAME_LEN + 1];
	char			user_path[PATH_MAX];
	int				server_sock;
	int				data_sock;
	int				data_port;
	char			data_ip[17];
}					t_env;

typedef struct		s_key_val
{
	void			*key;
	void			*val;
}					t_key_val;

extern const char * const g_ftp_reply_msg[];

/*
** --------------------------------- CMD_ENUM ----------------------------------
*/

enum ftp_reply_code {
	FTP_DATA_CON_ALRDY_OPEN = 1,
	FTP_FILE_STAT_OK,
	FTP_CMD_OK,
	FTP_CMD_UNK,
	FTP_SYST_STAT,
	FTP_DIR_STAT,
	FTP_FILE_STAT,
	FTP_HELP_MSG,
	FTP_SYST_NAME,
	FTP_SERV_RDY,
	FTP_LOGGED_OUT,
	FTP_DATA_CON_OPEN,
	FTP_DATA_CON_CLOSE,
	FTP_PASV_MODE,
	FTP_LOGGED_IN,
	FTP_REQ_ACT_OK,
	FTP_PATH_CREATED,
	FTP_NEED_PASS,
	FTP_NEED_ACC,
	FTP_ACT_PENDING,
	FTP_SERV_NOT_AVAIL,
	FTP_NO_DATA_CON,
	FTP_CON_CLOSE,
	FTP_FILE_BUSY,
	FTP_SYNT_ERR,
	FTP_SYNT_ERR_PAR,
	FTP_SYNT_ERR_UNK_CMD,
	FTP_SYNT_BAD_SEQ,
	FTP_NOT_LOGGED,
	FTP_FILE_NOT_AVAIL,
	FTP_UNK_TYPE,
	FTP_EXCEED_ALLOC,
	FTP_FILE_NOT_PERM
};

/*
** -----------------------------------------------------------------------------
** --------------------------------- PROTOTYPES --------------------------------
** -----------------------------------------------------------------------------
*/

int			err_msg(int ret, char *msg);
int			err_answer(int ret, char *answer, int idx);
void		ft_strtoupper(char *cmd);
void		server_usage(char *prog_name);
int			log_print(void);
int			log_print_user_msg(char *user, int user_id, char *cmd);

int			create_server(int port);
int			init_server_file_system(t_env *env);

void		init_cmd_hash(t_hash_list *hash);
int			process_cmds(t_env *env, char *input_cmd);

int			multi_client_handler(t_env *env, int sock);
int			check_port_range(char *port_str);


int			is_dir(char *path);
int			is_file(char *path);
int			is_pathvalid(char *root, char *path);
void		get_rootpath(char *root, char *path, char *buff);
int			ft_abspath(char *root, char *path, char *buff);

void		free_split(char **split);

int			is_dir(char *path);
int			is_file(char *path);


/*
** ---------------------------------- COMMANDS ---------------------------------
*/


int			user(t_env *env, char *param);
int			quit(t_env *env, char *param);
int			syst(t_env *env, char *param);
int			mkd(t_env *env, char *param);
int			noop(t_env *env, char *param);
int			rmd(t_env *env, char *param);
int			cdup(t_env *env, char *param);
int			cwd(t_env *env, char *param);
int			pwd(t_env *env, char *param);
int			port(t_env *env, char *param);
int			list(t_env *env, char *param);
int			stor(t_env *env, char *param);
int			retr(t_env *env, char *param);

#endif
