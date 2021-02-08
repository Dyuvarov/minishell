/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:10:09 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/08 15:06:00 by fmoaney          ###   ########.fr       */
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
	if (env == NULL)
		return (-1);
	if (args[0] != NULL)
		return (print_env_error(args[0]));
	while (*env)
		if (ft_putendl_fd(*env++, 1) == -1)
			return (errno);
	return (0);
}
