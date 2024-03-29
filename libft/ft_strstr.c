/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:44:41 by fmoaney           #+#    #+#             */
/*   Updated: 2020/12/23 22:05:23 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	const char *t1;
	const char *t2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (*s1)
	{
		if (*s1 == *s2)
		{
			t1 = s1;
			t2 = s2;
			while (*t1 == *t2 && *t2)
			{
				t1++;
				t2++;
			}
			if (*t2 == '\0')
				return ((char *)s1);
		}
		s1++;
	}
	return (NULL);
}
