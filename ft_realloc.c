/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:58:53 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/30 18:00:11 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *buf, size_t old_size, size_t new_size)
{
	void	*new_buf;

	if (new_size > old_size)
	{
		if ((new_buf = malloc(new_size)) != NULL)
		{
			ft_memcpy(new_buf, buf, old_size);
			free(buf);
		}
		return (new_buf);
	}
	else
		return (buf);
}

/*
** if index mod BUFFER_SIZE == 0:
**		need realloc
** else:
**		return without affecting
*/

void	*safe_realloc(void *buf, size_t index, size_t memsz)
{
	return (index == 0 || index % BUFFER_SIZE ? buf : \
			ft_realloc(buf, index * memsz, (index + BUFFER_SIZE) * memsz));
}

/*
** NULL-terminates final arr
**
** Ideally, need to make a reallocation to free up extra memory:
** 		res = realloc(arr, GET_OLD_SIZE(size) * membsz, membsz * (size + 1));
** 
** Returns: reallocated NULL-terminated array
*/

void	*normalize_arr(void *arr, size_t size, size_t membsz)
{
	char *res;

	res = (char *)arr;
	if (res)
		ft_bzero(res + size * membsz, membsz);
	return (res);
}
