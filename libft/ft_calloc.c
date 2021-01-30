/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:47:24 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/02 11:47:39 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*cp;
	void	*mem;

	i = 0;
	if ((mem = malloc(nmemb * size)) == NULL)
		return (NULL);
	cp = (char *)mem;
	while (i < nmemb)
	{
		ft_bzero(cp, size);
		i++;
		cp += size;
	}
	return (mem);
}
