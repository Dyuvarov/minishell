/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:51:35 by fmoaney           #+#    #+#             */
/*   Updated: 2020/12/29 15:07:48 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int n;

	n = -1;
	if (s != NULL)
	{
		n = ft_putstr_fd(s, fd);
		if (n != -1)
			n += ft_putchar_fd('\n', fd);
	}
	return (n);
}
