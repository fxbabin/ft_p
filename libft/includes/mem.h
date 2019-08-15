/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 21:00:06 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/15 23:35:45 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

/*
** --------------------------------- INCLUDES -------------------------------
*/

# include <stdlib.h>

/*
** ----------------------------- MEMORY FUNCTIONS ------------------------------
*/

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
size_t				ft_memchrindex(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_memdel(void **ap);
int					**ft_int2alloc(size_t size, size_t len);
char				**ft_char2alloc(size_t size, size_t len);
void				**ft_memalloc2(size_t si1, size_t si2, size_t size);
void				ft_free2(void **tab);
void				*ft_memdup(const void *s, size_t i);

#endif
