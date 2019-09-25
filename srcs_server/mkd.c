/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mkd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:13:44 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/25 19:43:12 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	set_buff(char *buff, char *s1, char *s2, char *s3)
{
	ft_strcpy(buff, s1);
	ft_strcat(buff, s2);
	ft_strcat(buff, s3);
}

int		mkd(t_env *env, const char **answer, char *param)
{
	char	abspath[PATH_MAX];
	DIR		*dir;

	if (!param)
		return (err_answer(-1, answer, FTP_SYNT_BAD_SEQ));
	ft_printf("'%s'\n", param);
	if (ft_abspath(env->user_path, param, (char*)(&abspath)) == -1)
		return (err_answer(-1, answer, FTP_SYNT_BAD_SEQ));
	if (!is_pathvalid(env->user_path, (char*)(&abspath)))
		return (err_answer(-1, answer, FTP_FILE_NOT_AVAIL));
	if ((dir = opendir((char*)(&abspath))))
	{
		set_buff((char*)&(env->answer), "521 \"", param, "\" directory already exists.\n");
		if ((closedir(dir)) == -1)
			return (err_msg(-1, "could not close ROOT_DIR"));
	}
	else if (errno == ENOENT)
	{
		if (mkdir((char*)(&abspath), 0755) == -1)
			return (err_answer(-1, answer, FTP_SYNT_BAD_SEQ));
		set_buff((char*)&(env->answer), "257 \"", param, "\" directory created.\n");
	}
	*answer = NULL;
	return (0);
}
