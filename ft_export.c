/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 22:17:01 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/08 17:16:16 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_correct_name(char *name, size_t len)
{
	if (len > 0 && (ft_isalpha(*name) || *name == '_'))
	{
		while (--len)
			if (!ft_isalnum(name[len]) && name[len] != '_')
				return (0);
	}
	else
		return (0);
	return (1);
}

static int	error(char *err_msg)
{
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (1);
}

static int	change_evn_var(char *var, size_t name_size, char **env)
{
	char	*eqsign;

	while (*env)
	{
		eqsign = ft_strchr(*env, '=');
		if ((size_t)(eqsign - *env) == name_size)
			if (ft_strncmp(*env, var, name_size) == 0)
			{
				free(*env);
				*env = ft_strdup(var);
				return (1);
			}
		env++;
	}
	return (0);
}

static int	print_env(char **env)
{
	char **clone;

	if ((clone = clone_envp(env)) == NULL)
		return (ENOMEM);
	bubblesort(clone);
	while (*clone)
	{
		if (ft_puts("declare -x ") == -1)
			return (errno);
		if (ft_putendl_fd(*clone++, 1) == -1)
			return (errno);
	}
	return (0);
}

int			ft_export(char **vars, char ***env)
{
	int		size;
	size_t	name_size;
	char	*var;
	char	*eqsign;

	size = get_size(*env);
	if (vars[0] == NULL)
		return (print_env(*env));
	while ((var = *vars++) != NULL)
	{
		eqsign = ft_strchr(var, '=');
		name_size = eqsign ? (size_t)(eqsign - var) : ft_strlen(var);
		if (!is_correct_name(var, name_size))
			return (error("minishell: export: not a valid identifier"));
		if (eqsign && !change_evn_var(var, name_size, *env))
		{
			if ((*env = ft_realloc(*env, sizeof(char *) * size,
					sizeof(char *) * (size + 2))) == NULL)
				return (ENOMEM);
			(*env)[size] = ft_strdup(var);
			(*env)[++size] = NULL;
		}
	}
	return (0);
}
