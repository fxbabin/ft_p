/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:17:39 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/12 17:18:09 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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
	//ft_printf("1::'%s'\n", answer_buff);
}
