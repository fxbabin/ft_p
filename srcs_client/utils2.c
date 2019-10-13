/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:47:27 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/13 18:48:08 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	bufferize_cmd(char *buff, char *cmd, char *param)
{
	ft_bzero(buff, 128);
	ft_strcpy(buff, cmd);
	if (param)
		ft_strncat(buff, param, 122);
	ft_strcat(buff, "\n");
}
