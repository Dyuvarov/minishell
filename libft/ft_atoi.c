/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:54:50 by fmoaney           #+#    #+#             */
/*   Updated: 2020/12/12 21:04:42 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	unsigned long int	res;
	int					sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		sign = *str++ == '-' ? -sign : sign;
	while (ft_isdigit(*str))
	{
		res = res * 10 + *str++ - '0';
		if (res > LONG_MAX)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
	}
	return (res * sign);
}
