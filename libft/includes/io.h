/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 01:21:57 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/18 00:38:55 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <unistd.h>
# include <fcntl.h>

/*
** --------------------------------- MACROS ---------------------------------
*/

# define BUF_SIZE 128

/*
** ------------------------------- STRUCTURES ---------------------------------
*/

typedef struct		s_gnl
{
	char			buff[BUF_SIZE + 1];
	int				fd;
	struct s_gnl	*next;
}					t_gnl;

/*
** ---------------------------- IO FUNCTIONS ---------------------------------
*/

void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putendl(const char *s);
void				ft_putnbr(int nb);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
int					sget_next_char(const int fd, char **line, char c);
int					get_next_char(const int fd, char **line,
						char *buff, char c);
int					get_next_line(const int fd, char **line);
int					sget_next_line(const int fd, char **line);

#endif
