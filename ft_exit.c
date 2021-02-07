/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:35:33 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/07 15:37:55 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	ft_exit(char **args)
{
	int exit_code;

	write(1, "exit\n", 5);
	if (args[0] && args[1])
	{
		handle_error(MANY_ARGS, "exit");
		return (1);
	}
	if (args[0] && ft_strlen(args[0]) != 0)
		exit_code = ft_atoi(args[0]);
	else
		exit_code = 0;
	exit(exit_code);
}

int	minishell_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
}
