/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 00:19:46 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/17 16:41:41 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ft_printf.h"
#include "mem.h"
#include "str.h"

static void		add_option(char **opt, char flag, const char *opts)
{
	char	*t;
	int		b;

	b = 0;
	if (!(t = (char*)ft_memalloc(2 * sizeof(char))))
		return ;
	ft_memcpy(t, &flag, 1);
	if (ft_charinset(flag, *opt))
		b++;
	if (b == 0)
		ft_strcat(*opt, t);
	ft_strdel(&t);
}

static int		parse_options(char **opt, char **argv, int *i,
		const char *opts)
{
	int		y;

	y = 0;
	while (argv[*i][++y])
	{
		if (ft_charinset(argv[*i][y], opts))
			add_option(opt, argv[*i][y], opts);
		else
		{
			ft_dprintf(2, "%s: illegal option -- %c\n", argv[0], argv[*i][y]);
			return (0);
		}
	}
	return (1);
}

char			*ft_getopt(int argc, char **argv, const char *opts)
{
	char	**tabopt;
	char	*opt;
	int		i;

	i = 0;
	if (!(tabopt = (char**)ft_split((char*)opts, ";")))
		return (NULL);
	if (!(opt = (char*)ft_memalloc((ft_strlen(opts) + 1) * sizeof(char))))
		return (NULL);
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "--"))
			break ;
		if (argv[i][0] != '-')
			break ;
		if (!parse_options(&opt, argv, &i, tabopt[0]))
		{
			ft_free2((void**)tabopt);
			ft_strdel(&opt);
			return (NULL);
		}
	}
	ft_free2((void**)tabopt);
	return (opt);
}
