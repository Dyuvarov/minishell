/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:51:30 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/02 11:51:32 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char			*ps;
	unsigned char	cc;

	cc = (unsigned char)c;
	ps = (char *)s;
	while (n-- > 0)
		*ps++ = cc;
	return (s);
}
