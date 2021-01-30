/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:51:39 by fmoaney           #+#    #+#             */
/*   Updated: 2020/12/14 17:32:07 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char			c;
	unsigned int	un;

	if (n < 0)
		write(fd, "-", 1);
	un = (n < 0) ? -((unsigned int)n) : (unsigned int)n;
	if (un / 10)
		ft_putnbr_fd(un / 10, fd);
	c = un % 10 + '0';
	return (write(fd, &c, 1));
}
