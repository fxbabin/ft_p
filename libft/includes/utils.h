/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 01:28:40 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 01:29:39 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
** ----------------------------- UTILS FUNCTIONS ------------------------------
*/

int					ft_isalnum(int c);
int					ft_iswp(char c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(char c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_abs(int nb);
void				ft_swap(int *a, int *b);
int					ft_tabsize(void **tab);
char				*ft_getopt(int argc, char **argv, const char *opts);

#endif
