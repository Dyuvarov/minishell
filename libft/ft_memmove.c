/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:51:28 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/02 12:12:52 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*cdst;
	char	*csrc;

	i = 0;
	csrc = (char *)src;
	cdst = (char *)dst;
	if (dst == NULL && src == NULL)
		return (dst);
	if (src >= dst)
		while (i < n)
			*cdst++ = csrc[i++];
	else
	{
		while (n-- > 0)
			cdst[n] = csrc[n];
	}
	return (dst);
}
