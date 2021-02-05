/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 11:36:33 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/05 12:22:04 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

void	input_signal_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 8);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		show_promt();
	}
}
