/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:36:33 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/10 19:08:34 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

void	input_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_last_res = 130;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_last_res = 131;
		write(1, "Quit: 3\n", 8);
	}
}

void	signal_handler(int sig)
{
	write(1, "\b\b  \b\b", 6);
	if (sig == SIGINT)
	{
		g_last_res = 1;
		write(1, "\n", 1);
		show_promt();
	}
}
