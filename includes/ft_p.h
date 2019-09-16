/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:02:19 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/16 12:20:09 by fbabin           ###   ########.fr       */
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

# define  PATH_MAX  1024

typedef struct		s_env
{
	char			base_path[PATH_MAX];
	char			base_len;
}					t_env;

enum ftp_reply {
	FTP_SYNT_CMD_OK,
};

int			err_msg(int ret, char *msg);
void		server_usage(char *prog_name);

int			create_server(int port);
int			multi_client_handler(int sock);
int			check_port_range(char *port_str);

#endif
