/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 22:21:54 by fbabin            #+#    #+#             */
/*   Updated: 2019/10/08 22:29:33 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		get_port(t_cenv *cenv, char *buff)
{
	char	*tmp;

	(void)buff;
	ft_strcpy(buff, "PORT ");
	if (!(tmp = ft_strreplace(cenv->data_ip, ".", ",")))
		return (-1);
	ft_strcat(buff, tmp);
	ft_strcat(buff, ",");
	free(tmp);
	if (!(tmp = ft_itoa(ft_atoi(cenv->tmp_port) / 256)))
		return (-1);
	ft_strcat(buff, tmp);
	ft_strcat(buff, ",");
	free(tmp);
	if (!(tmp = ft_itoa(ft_atoi(cenv->data_port) % 256)))
		return (-1);
	ft_strcat(buff, tmp);
	ft_strcat(buff, "\n");
	free(tmp);
	ft_printf("> %s\n", buff);
	return (0);
}

void	get_eprt(t_cenv *cenv, char *buff)
{
	ft_strcpy(buff, "EPRT |");
	ft_strcat(buff, cenv->data_ipv);
	ft_strcat(buff, "|");
	ft_strcat(buff, cenv->data_ip);
	ft_strcat(buff, "|");
	ft_strcat(buff, cenv->tmp_port);
	ft_strcat(buff, "|\n");
}

void	get_ipport(t_cenv *cenv, char *buff)
{
	if (cenv->data_ipv[0] == '2')
		get_eprt(cenv, buff);
	else
		get_port(cenv, buff);
}
