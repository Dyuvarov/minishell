/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:05:49 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/03 15:06:04 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Reads from STDIN
** c: char from stdin
** if c == 0 => EOF; if c == -1 => ERROR
**
** FIRST char must be ALPHA or '_'
** Chars after the first must be ALPHA, DIGIT or '_'
**
** BUFFER_SIZE >= 2
**
** The last char read returns to stdin buffer (ft_ungetch)
**
** Returns: env variable or NULL (if ERROR, EOF or such env var doesn't exist)
*/

char	*parse_dollar(char **env)
{
	int		i;
	int		c;
	char	*name;
	char	*res;

	i = 0;
	if ((name = (char *)malloc(BUFFER_SIZE)) == NULL)
		return (NULL);
	if ((c = ft_getch()) > 0 && (ft_isalpha(c) || c == '_'))
	{
		name[i++] = c;
		while (name && (c = ft_getch()) > 0 && (ft_isalnum(c) || c == '_'))
		{
			name = safe_realloc(name, i, sizeof(*name));
			name[i++] = c;
		}
		name[i] = '\0';
		res = get_env_var(name, env);
		free(name);
	}
	if (i == 0 && c == '?')
		res = ft_strdup("$?");
	else
		ft_ungetch();
	return (res);
}
