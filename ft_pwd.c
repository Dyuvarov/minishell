/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:21:11 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/31 14:37:41 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cur_path(void)
{
	size_t	size;
	char	*path;

	errno = 0;
	size = BUFFER_SIZE;
	if ((path = (char *)malloc(sizeof(char) * size)) == NULL)
		return (NULL);
	while (getcwd(path, size) == NULL && errno == ERANGE)
	{
		errno = 0;
		size *= 2;
		if ((path = ft_realloc(path, size / 2, size)) == NULL)
			return (NULL);
	}
	return (path);
}

int		ft_pwd(void)
{
	char	*path;

	path = get_cur_path();
	if (path == NULL)
		return (errno ? errno : ENOMEM);
	errno = 0;
	ft_putendl_fd(path, 1);
	free(path);
	return (errno);
}
