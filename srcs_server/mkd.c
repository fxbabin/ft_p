/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mkd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:13:44 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/22 16:44:04 by fbabin           ###   ########.fr       */
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
	DIR		*dir;
	
	if (!param)
		return (err_answer(-1, answer, FTP_SYNT_BAD_SEQ));
	if ((dir = opendir(param)))
	{
		set_buff((char*)&(env->buff), "521 \"", param, "\" directory already exists.\n");
		if ((closedir(dir)) == -1)
			return (err_msg(-1, "could not close ROOT_DIR"));
	}
	else if (errno == ENOENT)
	{
		set_buff((char*)&(env->buff), "257 \"", param, "\" directory created.\n");
		mkdir(param, 0755);
	}
	*answer = NULL;
	return (0);
}

//257 "/usr/dm/pathname" directory created
