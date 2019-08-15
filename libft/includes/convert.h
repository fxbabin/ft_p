/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 01:04:46 by fbabin            #+#    #+#             */
/*   Updated: 2018/04/16 01:05:26 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_H
# define CONVERT_H

/*
** --------------------------- CONVERSION FUNCTIONS ----------------------------
*/

int					ft_atoi(const char *str);
long				ft_atol(const char *str);
long long			ft_atoll(const char *str);
unsigned long long	ft_atollu(const char *str);
char				*ft_itoa(int nb);
char				*ft_ftoa(double nb, int prec);
char				*ft_ltoa(long nb);
char				*ft_lltoa(long long nb);
char				*ft_llutoa(unsigned long long nb);
char				*ft_itoa_base(int nb, const char *base);
char				*ft_ltoa_base(long nb, const char *base);
char				*ft_lltoa_base(long long nb, const char *base);
char				*ft_llutoa_base(unsigned long long nb, const char *base);
long long			ft_long_atoi(const char *str);

#endif
