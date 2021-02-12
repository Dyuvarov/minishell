/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:35:33 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/12 17:13:23 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

static int	handle_args(char **args)
{
	int	i;
	int	error;
	int exit_code;

	error = 0;
	i = 0;
	while (args[0][i])
	{
		if (!ft_isdigit(args[0][i]) && args[0][i] != '-' && args[0][i] != '+')
			error = 1;
		++i;
	}
	if (error)
	{
		handle_exit_error(args[0]);
		exit(255);
	}
	if (args[1])
	{
		handle_error(MANY_ARGS, "exit");
		return (1);
	}
	exit_code = ft_atoi(args[0]);
	return (exit_code);
}

int			ft_exit(char **args)
{
	int exit_code;

	if (!g_prepipe)
		write(1, "exit\n", 5);
	if (args && args[0])
	{
		if ((exit_code = handle_args(args)) == 1)
			return (1);
	}
	else
		exit_code = 0;
	exit(exit_code);
}

int			minishell_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
}
