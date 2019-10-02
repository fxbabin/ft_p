/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 15:16:04 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/02 18:10:17 by fbabin           ###   ########.fr       */
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
	[FTP_SERV_NOT_AVAIL] = "421 Service not available, closing control "
	"connection.\n",
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

/*
	[FTP_DATA_CON_ALRDY_OPEN] = "125 Data connection already open; transfer
								 starting.\n",
			//[FTP_CMD_UNK] = "202 Command not implemented, superfluous at this
		//				 site.\n",
		//[FTP_SYST_STAT] = "211 System status, or system help reply.\n",
		//[FTP_DIR_STAT] = "212 Directory status.\n",
		//[FTP_FILE_STAT] = "213 File status.\n",
		//[FTP_HELP_MSG] = "214 Help message.\n",
		//[FTP_DATA_CON_OPEN] = "225 Data connection open; no transfer in
		//					   progress.\n",
		//[FTP_PASV_MODE] = "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\n",
		//[FTP_PATH_CREATED] = "257 PATH created.\n",
		//[FTP_NEED_PASS] = "331 User name okay, need password.\n",
		//[FTP_NEED_ACC] = "332 Need account for login.\n",
		//[FTP_ACT_PENDING] = "350 Requested file action pending further "
		//					 "information.\n",
		//[FTP_NO_DATA_CON] = "425 Can't open data connection.\n",
		//[FTP_CON_CLOSE] = "426 Connection closed; transfer aborted.\n",
		//[FTP_FILE_BUSY] = "450 Action not taken: File unavailable.\n",
		//[FTP_UNK_TYPE] = "551 Requested action aborted: page type unknown.\n",
		//[FTP_EXCEED_ALLOC] = "552 Requested file action aborted: Exceeded "
		//					  "storage allocation\n",
*/
