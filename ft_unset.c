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
	while (*envp[n])
	{
		if (*envp[n + 1])
		{
			free(*envp[n]);
			*envp[n] = ft_strdup(*envp[n+1]);
			if (!(*envp[n]))
				return (0);
			++n;
		}
		else
		{
			free(*envp[n]);
			*envp[n] = NULL;
		}
	}
	return (1);
}

int ft_unset(char **vars, char ***envp)
{
	int		i;
	int 	j;
	char 	*eqsign;

	i = 0;
	while (vars[i])
	{
		j = 0;
		while (*envp[j])
		{
			eqsign = ft_strchr(*envp[j], '=');
			if (eqsign)
			{
				if ((ft_strncmp(vars[i], *envp[j], eqsign - *envp[j])) == 0)
				{
					if (!restruct_envp(envp, j))
					{
						return (0); //malloc errror
					}
				}
			}
			++j;
		}
		++i;
	}
	return (1);
}