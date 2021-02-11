/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:35:33 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/11 21:11:03 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	ft_exit(char **args)
{
	int exit_code;

	if (!g_prepipe)
		write(1, "exit\n", 5);
	if (args[0] && args[1])
	{
		handle_error(MANY_ARGS, "exit");
		return (1);
	}
	if (args[0] && ft_strlen(args[0]) != 0)
	{
		exit_code = ft_atoi(args[0]);
		if (exit_code == 0 && (ft_strlen(args[0]) != 1))
			exit_code = handle_exit_error(args[0]);	
	}
	else
		exit_code = 0;
	exit(exit_code);
}

int	minishell_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
}
