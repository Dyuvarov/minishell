/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:51:26 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/02 11:51:28 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char *cdst;
	char *csrc;

	cdst = (char *)dest;
	csrc = (char *)src;
	if (dest == NULL && src == NULL)
		return (dest);
	while (n-- > 0)
		*cdst++ = *csrc++;
	return (dest);
}
