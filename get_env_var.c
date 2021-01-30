/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:51:11 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/21 19:41:33 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Returns env variable
*/

char	*get_env_var(char *name, char **env)
{
	size_t	len;
	char	*eqsign;

	len = ft_strlen(name);
	while (*env)
	{
		eqsign = ft_strchr(*env, '=');
		if ((size_t)(eqsign - *env) == len)
			if (ft_strnstr(*env, name, len))
				return (eqsign + 1);
		env++;
	}
	return (NULL);
}
