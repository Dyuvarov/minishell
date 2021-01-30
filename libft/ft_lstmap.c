/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:06:43 by fmoaney           #+#    #+#             */
/*   Updated: 2020/11/03 17:45:47 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *res;

	res = NULL;
	if (lst != NULL)
	{
		if ((res = ft_lstnew(f(lst->content))) == NULL)
			return (NULL);
		res->next = ft_lstmap(lst->next, f, del);
		if (res->next == NULL && lst->next != NULL)
		{
			del(res->content);
			free(res);
			return (NULL);
		}
	}
	return (res);
}
