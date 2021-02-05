/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abs_path_command2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:42:53 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/05 12:51:30 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_abs_path(char *dir, char *file_name)
{
	char *t;
	char *r;

	r = NULL;
	if ((t = ft_strjoin(dir, "/")) != NULL)
	{
		r = ft_strjoin(t, file_name);
		free(t);
	}
	return (r);
}

int			is_curdir(char *p)
{
	return ((p)[0] == '.' && (p)[1] == '/');
}

int			is_pardir(char *p)
{
	return ((p)[0] == '.' && (p)[1] == '.' && (p)[2] == '/');
}

int			is_path(char *p)
{
	return (ft_strchr((p), '/') != NULL);
}

int			is_equal(char *s1, char *s2)
{
	return (ft_strncmp((s1), (s2), ft_strlen(s1)) == 0);
}
