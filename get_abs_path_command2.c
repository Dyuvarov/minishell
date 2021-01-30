/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abs_path_command2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:42:53 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/26 18:24:54 by fmoaney          ###   ########.fr       */
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
