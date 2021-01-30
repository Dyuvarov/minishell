/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:38:46 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/29 22:18:00 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *g_bufp = 0;
static int	g_n = 0;

/*
** Buffered read from stdin
**
** Returns: unsigned char
** 			or EOF == 0; ERROR == -1
*/

int		ft_getch(void)
{
	static char buf[BUFFER_SIZE >= 0 ? BUFFER_SIZE : 0];
	extern char *g_bufp;
	extern int	g_n;

	if (g_n <= 0)
	{
		g_n = read(0, buf, BUFFER_SIZE);
		g_bufp = buf;
	}
	if (--g_n >= 0)
		return ((unsigned char)*g_bufp++);
	else
		return (g_n == -1 ? 0 : -1);
}

/*
** Returns character to the buffer
*/

void	ft_ungetch(void)
{
	extern char *g_bufp;
	extern int	g_n;

	g_bufp--;
	g_n++;
}
