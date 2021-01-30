/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:52:00 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/02 16:34:37 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char	*s;
	size_t		size;

	if (src == NULL)
		return (0);
	size = dstsize == 0 ? 1 : dstsize;
	s = src;
	while (size-- > 1 && (*dst++ = *s++) != '\0')
		;
	if (size == 0)
	{
		if (dstsize != 0)
			*dst = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}
