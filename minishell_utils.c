/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 13:42:04 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/01 15:57:35 by fmoaney          ###   ########.fr       */
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

int		decrease_shlvl(char *shlvl_val, char ***env)
{
	int		err;
	char	*shlvl_var[2];
	
	err = 0;
	shlvl_var[1] = NULL;
	if (shlvl_val != NULL)
	{
		if ((shlvl_val = ft_itoa(ft_atoi(shlvl_val) - 1)) == NULL)
			return (-1);
		shlvl_var[0] = ft_strjoin("SHLVL=", shlvl_val);
		free(shlvl_val);
		if (shlvl_var[0] == NULL)
			return (-1);
		err = ft_export(shlvl_var, env);
		free(shlvl_var[0]);
	}
	else
	{
		shlvl_var[0] = ft_strdup("SHLVL");
		err = ft_unset(shlvl_var, env);
	}
	return (err);
}

int		increase_shlvl(char *shlvl_val, char ***env)
{
	char	*shlvl_var[2];
	int		err;

	shlvl_val = shlvl_val ? shlvl_val : "";
	if ((shlvl_val = ft_itoa(ft_atoi(shlvl_val) + 1)) == NULL)
		return (-1);
	shlvl_var[0] = ft_strjoin("SHLVL=", shlvl_val);
	shlvl_var[1] = NULL;
	free(shlvl_val);
	if (shlvl_var[0] == NULL)
		return (-1);
	err = ft_export(shlvl_var, env);
	free(shlvl_var[0]);
	return (err);
}
