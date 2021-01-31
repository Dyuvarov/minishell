/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:42:04 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/31 18:03:29 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_size(char **buf)
{
	int size;

	size = 0;
	while (*buf++)
		size++;
	return (size);
}

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

int		increase_shlvl(char **env)
{
	char	*shlvl_var;
	char	*shlvl_val;
	char	*eqsign;
	size_t	len;

	len = 5;
	shlvl_val = NULL;
	while (*env && shlvl_val == NULL)
	{
		eqsign = ft_strchr(*env, '=');
		if ((size_t)(eqsign - *env) == len)
			if (ft_strnstr(*env, "SHLVL", len))
				shlvl_val = (eqsign + 1);
		env++;
	}
	if (*env == NULL || (shlvl_val = ft_itoa(ft_atoi(shlvl_val) + 1)) == NULL)
		return (-1);
	env--;
	(*env)[eqsign - *env + 1] = '\0';
	shlvl_var = ft_strjoin(*env, shlvl_val);
	free(*env);
	free(shlvl_val);
	*env = shlvl_var;
	return (0);
}
