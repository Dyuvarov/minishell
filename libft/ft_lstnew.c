/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:07:18 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/03 17:45:52 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *l;

	if ((l = (t_list *)malloc(sizeof(t_list))) != NULL)
	{
		l->content = content;
		l->next = NULL;
	}
	return (l);
}
