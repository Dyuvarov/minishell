/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:42:04 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/01 13:52:36 by fmoaney          ###   ########.fr       */
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

int		increase_shlvl(char ***env)
{
	char	*shlvl_var[2];
	char	*shlvl_val;
	int		err;

	if ((shlvl_val = get_env_var("SHLVL", *env)) == NULL)
		shlvl_val = "";
	if ((shlvl_val = ft_itoa(ft_atoi(shlvl_val) + 1)) == NULL)
		return (-1);
	shlvl_var[0] = ft_strjoin("SHLVL=", shlvl_val);
	shlvl_var[1] = NULL;
	ft_putendl_fd(shlvl_var[0], 1);
	free(shlvl_val);
	if (shlvl_var[0] == NULL)
		return (-1);
	err = ft_export(shlvl_var, env);
	free(shlvl_var[0]);
	return (err);
}
