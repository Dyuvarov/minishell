/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:26:54 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/02 11:49:32 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	len;
	unsigned int	un;
	unsigned int	ut;

	len = (n < 0) ? 2 : 1;
	un = (n < 0) ? -((unsigned int)n) : (unsigned int)n;
	ut = un;
	while ((ut /= 10) > 0)
		len++;
	if ((s = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	*s++ = un % 10 + '0';
	while ((un /= 10) > 0)
		*s++ = un % 10 + '0';
	n < 0 ? *s++ = '-' : 0;
	*s = '\0';
	s = (s - len);
	while (--len > un)
	{
		ut = *(s + un);
		*(s + un++) = *(s + len);
		*(s + len) = ut;
	}
	return (s);
}
