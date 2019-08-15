/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 01:24:00 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/17 15:39:50 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include <stdlib.h>
# include <string.h>

/*
** --------------------------------- STRUCTURES -------------------------------
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*
** --------------------------- LIST FUNCTIONS --------------------------------
*/

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *fresh);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstcreate(void *content, size_t cs);
void				ft_lstpushback(t_list **begin_list, void *content,
						size_t cs);
void				ft_lstpushfront(t_list **begin_list, void *content,
						size_t cs);
int					ft_lstsize(t_list *begin_list);
t_list				*ft_lstlast(t_list *begin_list);
void				ft_lstclear(t_list **begin_list);
t_list				*ft_lstatpos(t_list *begin_list, unsigned int nbr);
void				ft_lstreverse(t_list **begin_list);
t_list				*ft_lstfind(t_list *begin_list,
						void *data_ref, int (*cmp)(), size_t size);
void				ft_lstremoveif(t_list **begin_list,
						void *content_ref, int (*cmp)(), size_t size);
void				ft_lstmerge(t_list **begin_list1, t_list *begin_list2);
void				ft_lstdump(t_list **list);
void				ft_lstsort(t_list **list);
void				ft_eldel(void *content, size_t content_size);
void				ft_elemdel(void *content, size_t content_size);

#endif
