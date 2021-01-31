/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:17:20 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/21 18:17:42 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getchar(int fd)
{
	static char buf[BUFFER_SIZE >= 0 ? BUFFER_SIZE : 0];
	static char *bufp = buf;
	static int	n = 0;

	if (n <= 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		bufp = buf;
	}
	return (--n >= 0) ? (unsigned char)*bufp++ : n;
}
