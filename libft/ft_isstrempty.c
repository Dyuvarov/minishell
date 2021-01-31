/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrempty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 18:46:42 by fmoaney           #+#    #+#             */
/*   Updated: 2020/12/12 20:57:26 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isstrempty(const char *s)
{
	if (s == NULL)
		return (1);
	while (*s && ft_isspace(*s))
		s++;
	return (!*s);
}
