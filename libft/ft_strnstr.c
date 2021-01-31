/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:29:58 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/02 16:28:17 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int			little_len;
	const char	*pb;
	const char	*pl;

	if (*little == '\0')
		return ((char *)big);
	little_len = ft_strlen(little);
	while (*big && (long int)len - little_len >= 0)
	{
		if (*big == *little)
		{
			pl = little;
			pb = big;
			while (*pb == *pl && *pl != '\0')
			{
				pb++;
				pl++;
			}
			if (*pl == '\0')
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
