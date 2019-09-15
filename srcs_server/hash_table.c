/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:12:46 by fbabin            #+#    #+#             */
/*   Updated: 2019/09/15 19:34:09 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#define HASH_TSIZE 30

typedef struct			s_hash_list
{
	void				*key;
	void				*value;
	struct s_hash_list	*next;
}						t_hash_list;

int		hash_func(char *str, int hash_tsize)
{
	int		hash;
	int		i;

	i = -1;
	hash = 5381;
	while (str[++i])
		hash = (((hash << 5) + hash) + str[i]) % hash_tsize;
	return (hash % hash_tsize);
}

int		hash_strcmp(void *s1, void *s2)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = -1;
	tmp1 = (char*)s1;
	tmp2 = (char*)s2;
	while (tmp1[++i] || tmp2[i])
	{
		if (tmp1[i] != tmp2[i])
			return (tmp1[i] - tmp2[i]);
	}
	return (0);
}

void	hash_add_key_val(t_hash_list *hash_table, void *key, void *val, 
		int (cmp)(void*, void*))
{
	int				hash_idx;
	t_hash_list		*tmp;

	hash_idx = hash_func((char*)key, HASH_TSIZE);
	tmp = hash_table;
	if (hash_table[hash_idx].key != NULL)
	{
		while (tmp->next)
		{
			if (cmp(tmp[hash_idx].key, key) == 0)
				break ;
			tmp = tmp->next;
		}
		if (cmp(tmp[hash_idx].key, key) != 0)
		{
			if (!(tmp->next = (t_hash_list*)malloc(sizeof(t_hash_list))))
				return ;
			tmp = tmp->next;
		}
	}
	tmp[hash_idx].key = key;
	tmp[hash_idx].value = val;
	tmp[hash_idx].next = NULL;
}

void	*hash_get_val(t_hash_list *hash_table, void *key,
				int (cmp)(void*, void*))
{
	int				hash_idx;
	t_hash_list		*tmp;

	hash_idx = hash_func((char*)key, HASH_TSIZE);
	tmp = hash_table;
	while (tmp)
	{
		if (cmp(tmp[hash_idx].key, key) == 0)
			return (tmp[hash_idx].value);
		tmp = tmp->next;
	}
	return (NULL);
}

int		main(void)
{
	t_hash_list		hash_table[HASH_TSIZE];

	printf("%s :: %d\n", "STRU", hash_func("STRU", HASH_TSIZE));
	printf("%s :: %d\n", "ABOR", hash_func("ABOR", HASH_TSIZE));
	hash_add_key_val((t_hash_list*)(&hash_table), "aa", "sufeheuhkufehkufh", hash_strcmp);
	hash_add_key_val((t_hash_list*)(&hash_table), "STRU", "tata", hash_strcmp);
	hash_add_key_val((t_hash_list*)(&hash_table), "ABOR", "tati", hash_strcmp);
	printf("%s -> %s\n", "aa", hash_get_val((t_hash_list*)(&hash_table), "aa", hash_strcmp));
	printf("%s -> %s\n", "STRU", hash_get_val((t_hash_list*)(&hash_table), "STRU", hash_strcmp));
	printf("%s -> %s\n", "ABOR", hash_get_val((t_hash_list*)(&hash_table), "ABOR", hash_strcmp));
	return (0);
}
