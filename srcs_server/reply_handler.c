/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 15:16:04 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/11 17:15:28 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

const char *const g_ftp_reply_msg[] = {
	[FTP_FILE_STAT_OK] = "150 File status okay; about to open data"
	"connection.\n",
	[FTP_CMD_OK] = "200 Command okay.\n",
	[FTP_SYST_NAME] = "215 system name.\n",
	[FTP_SERV_RDY] = "220 Service ready for new user.\n",
	[FTP_LOGGED_OUT] = "221 Service closing control connection.\n",
	[FTP_DATA_CON_CLOSE] = "226 Closing data connection.\n",
	[FTP_LOGGED_IN] = "230 User logged in, proceed.\n",
	[FTP_REQ_ACT_OK] = "250 Requested file action okay, completed.\n",
	[FTP_NEED_PASS] = "331 User name okay, need password.\n",
	[FTP_SERV_NOT_AVAIL] = "421 Service not available, closing control "
	"connection.\n",
	[FTP_DATA_CON_KO] = "425 Can't open data connection.\n",
	[FTP_SYNT_ERR] = "500 Syntax error, command unrecognized.\n",
	[FTP_SYNT_ERR_PAR] = "501 Syntax error in parameters "
	"or arguments.\n",
	[FTP_SYNT_ERR_UNK_CMD] = "502 Command not implemented.\n",
	[FTP_SYNT_BAD_SEQ] = "503 Bad sequence of commands.\n",
	[FTP_NOT_LOGGED] = "530 Not logged in.\n",
	[FTP_FILE_NOT_AVAIL] = "550 Requested action not taken: File "
	"unavailable.\n",
	[FTP_FILE_NOT_PERM] = "553 Requested action not taken: name not "
	"allowed\n",
};
