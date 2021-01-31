/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:53:12 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/02 16:37:28 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *res;
	char *ss;

	if (s == NULL)
		return (NULL);
	if ((ss = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	res = ss;
	while (*s != '\0' && start-- > 0)
		s++;
	while (len > 0 && (*ss = *s) != '\0')
	{
		ss++;
		s++;
		len--;
	}
	*ss = '\0';
	return (res);
}
