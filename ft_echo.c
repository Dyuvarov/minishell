/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:46:00 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/07 13:10:57 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int fl_n;

	fl_n = 0;
	if (args == NULL)
		return (-1);
	while (*args && ft_strequal(*args, "-n"))
	{
		args++;
		fl_n = 1;
	}
	while (*args)
	{
		if (ft_puts(*args++) == -1)
			return (errno);
		if (*args != NULL)
			if (ft_putchar_fd(' ', 1) == -1)
				return (errno);
	}
	if (!fl_n)
		if (ft_putchar_fd('\n', 1) == -1)
			return (errno);
	return (0);
}
