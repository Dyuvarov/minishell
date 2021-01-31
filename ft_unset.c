/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:32:28 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/01/28 10:32:31 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	restruct_envp(char ***envp, int n)
{
	char 	**env;

	env = *envp;
	while (env[n])
	{
		if (env[n + 1])
		{
			free(env[n]);
			env[n] = ft_strdup(env[n+1]);
			if (!(env[n]))
				return (0);
			++n;
		}
		else
		{
			free(env[n]);
			env[n] = NULL;
		}
	}
	return (1);
}

int ft_unset(char **vars, char ***envp)
{
	int		i;
	int 	j;
	char 	*eqsign;
	char 	**env;

	i = 0;
	env = *envp;
	while (vars[i])
	{
		j = 0;
		while (env[j])
		{
			eqsign = ft_strchr(env[j], '=');
			if (eqsign)
			{
				if ((ft_strncmp(vars[i], env[j], eqsign - env[j])) == 0)
				{
					if (!restruct_envp(envp, j))
						return (0);
					return (1);
				}
			}
			++j;
		}
		++i;
	}
	return (1);
}