/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:51:52 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/02 11:51:53 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ns;

	len = ft_strlen(s);
	if ((ns = (char *)malloc(len + 1)) != NULL)
		ft_strlcpy(ns, s, len + 1);
	return (ns);
}
