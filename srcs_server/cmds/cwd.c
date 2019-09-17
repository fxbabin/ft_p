/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:42:11 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/12 17:18:21 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	change_dir(t_env *env, char **answer_buff, char *str)
{
	ft_printf("'%s'\n", str);
	//ft_printf("'%s'\n", str + 3);
	chdir(str + 3);
	get_curr_dir(env, *answer_buff);
	//ft_printf("2::'%s'\n", *answer_buff);

}
