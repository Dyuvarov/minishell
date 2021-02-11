/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:10:09 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/10 19:27:41 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_env_error(char *file)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(ENOENT), STDERR_FILENO);
	return (127);
}

int			ft_env(char **args, char **env)
{
	char	*eqsign;

	if (env == NULL)
		return (-1);
	if (args[0] != NULL)
		return (print_env_error(args[0]));
	while (*env)
	{
		eqsign = ft_strchr(*env, '=');
		if (eqsign)
			if (ft_putendl_fd(*env, 1) == -1)
				return (errno);
		env++;		
	}
	return (0);
}
