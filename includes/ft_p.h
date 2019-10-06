/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:02:19 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/06 22:56:27 by fbabin           ###   ########.fr       */
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

# define HASH_SIZE			184
# define ROOT_DIR			"./ROOT_DIR"
# define CMD_MAX_LEN		4
# define INPUT_MAX_LEN		128
# define MAX_USERS			128
# define USER_NAME_LEN		6
# define PASS_SALT			"xF"
# define IPV6_LEN			46
# define CMD_HASH_SIZE		142
/*
** -------------------------------- STRUCTURES ---------------------------------
*/

typedef struct				s_env
{
	char					answer[PATH_MAX + INPUT_MAX_LEN];
	char					users[MAX_USERS + 1];
	t_hash_list				hash[HASH_SIZE];
	char					root_path[PATH_MAX];
	char					is_logged;
	int						user_id;
	char					user_name[USER_NAME_LEN + 1];
	char					user_path[PATH_MAX];
	int						server_sock;
	int						data_sock;
	char					data_port[6];
	char					data_ip[IPV6_LEN];
}							t_env;

typedef struct				s_key_val
{
	void					*key;
	void					*val;
}							t_key_val;

typedef struct				s_cenv
{
	char					cmd[PATH_MAX + INPUT_MAX_LEN];
	char					reply[PATH_MAX + INPUT_MAX_LEN];
	t_hash_list				cmd_hash[CMD_HASH_SIZE];
	int						csock;
	int						data_sock;
	char					data_port[6];
	char					data_ip[IPV6_LEN];

}							t_cenv;

extern const char * const	g_ftp_reply_msg[];

/*
** --------------------------------- CMD_ENUM ----------------------------------
*/

enum	e_ftp_reply_code
{
	FTP_FILE_STAT_OK = 1,
	FTP_CMD_OK,
	FTP_SYST_NAME,
	FTP_SERV_RDY,
	FTP_LOGGED_OUT,
	FTP_DATA_CON_OPEN,
	FTP_DATA_CON_CLOSE,
	FTP_LOGGED_IN,
	FTP_REQ_ACT_OK,
	FTP_NEED_PASS,
	FTP_SERV_NOT_AVAIL,
	FTP_CON_CLOSE,
	FTP_SYNT_ERR,
	FTP_SYNT_ERR_PAR,
	FTP_SYNT_ERR_UNK_CMD,
	FTP_SYNT_BAD_SEQ,
	FTP_NOT_LOGGED,
	FTP_FILE_NOT_AVAIL,
	FTP_FILE_NOT_PERM
};

enum	e_help_client
{
	HELP_LS = 50,
	HELP_PWD,
	HELP_USER,
	HELP_CD,
	HELP_MKDIR,
	HELP_RMDIR,
	HELP_QUIT,
	HELP_PUT,
	HELP_GET,
	HELP_LLS,
	HELP_LPWD,
	HELP_LCD,
};

/*
** -----------------------------------------------------------------------------
** --------------------------------- PROTOTYPES --------------------------------
** -----------------------------------------------------------------------------
*/

/*
** ---------------------------- SERVER PROTO ---------------------------------
*/

int							err_msg(int ret, char *msg);
int							err_answer(int ret, char *answer, int idx);
void						ft_strtoupper(char *cmd);
void						server_usage(char *prog_name);
int							log_print(void);
int							log_print_user_msg(char *user, int user_id,
								char *cmd);
int							create_server(char *port);
int							init_server_file_system(t_env *env);

void						init_cmd_hash(t_hash_list *hash);
int							process_cmds(t_env *env, char *input_cmd);

int							multi_client_handler(t_env *env, int sock);
int							check_port_range(char *port_str);

int							is_dir(char *path);
int							is_file(char *path);
int							is_pathvalid(char *root, char *path);
void						get_rootpath(char *root, char *path, char *buff);
int							ft_abspath(char *root, char *path, char *buff);
void						free_split(char **split);
int							create_data_con(char *addr, char *port);

/*
** ---------------------------- SERVER COMMANDS ---------------------------------
*/

int							user(t_env *env, char *param);
int							quit(t_env *env, char *param);
int							syst(t_env *env, char *param);
int							mkd(t_env *env, char *param);
int							noop(t_env *env, char *param);
int							rmd(t_env *env, char *param);
int							cdup(t_env *env, char *param);
int							cwd(t_env *env, char *param);
int							pwd(t_env *env, char *param);
int							port(t_env *env, char *param);
int							list(t_env *env, char *param);
int							stor(t_env *env, char *param);
int							retr(t_env *env, char *param);
int							dele(t_env *env, char *param);
int							pass(t_env *env, char *param);
int							eprt(t_env *env, char *param);

/*
** ---------------------------- CLIENT PROTO ---------------------------------
*/

void						client_usage(char *prog_name);
int							create_client(char *addr, char *port);
int							client_handler(t_cenv *cenv);
int							receive_reply(t_cenv *cenv);
void						init_ccmd_hash(t_hash_list *hash);
int							process_ccmds(t_cenv *cenv, char *input_cmd);

int							cquit(t_cenv *cenv, char *param);
int							cuser(t_cenv *cenv, char *param);

#endif
