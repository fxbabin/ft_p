/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 22:13:52 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/12 17:19:35 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		err_msg(int ret, char *msg)
{
	ft_dprintf(2, "%kError%k :: %s\n", LRED, RESET, msg);
	return (ret);
}

void	server_usage(char *prog_name)
{
	ft_printf("Usage: %s <port [1024-65535]>\n", prog_name);
	exit(-1);
}
