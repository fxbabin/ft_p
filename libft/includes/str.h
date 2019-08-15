/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 01:27:13 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 22:34:18 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <string.h>
# include <stdlib.h>

/*
** ----------------------------- STRING FUNCTIONS ------------------------------
*/

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *s1, const char *s2, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmjoin(char *s1, char const *s2, int len1, int len2);
char				*ft_strtrim(const char *s);
char				**ft_strsplit(const char *str, char c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strchrindex(const char *str, char c);
int					ft_charinset(char c, const char *charset);
char				*ft_strjoinclr(char *s1, char *s2, int b);
char				*ft_strnjoinclr(char *s1, char *s2, int len, int b);
char				*ft_strreplace(char *str, const char *old,
						const char *fresh);
int					ft_strspn(const char *s, const char *charset);
int					ft_strcspn(const char *s, const char *charset);
char				ft_strbspn(const char *s, const char *charset);
char				ft_strbcspn(const char *s, const char *charset);
char				**ft_split(char *str, char *charset);

#endif
