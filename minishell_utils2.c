/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:41:18 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/04 18:49:21 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define LRS "$?"

static char	*ft_strcpy(char *dst, char *src)
{
	char *r;

	r = dst;
	while ((*dst++ = *src++))
		;
	return (r);
}

char		*ft_strreplace(char *dst, const char *old, const char *new)
{
	int		i;
	int		new_sz;
	int		old_sz;
	char	*res;

	if ((i = ft_indexof(dst, old, 0)) == -1)
		return (ft_strdup(dst));
	new_sz = ft_strlen(new);
	old_sz = ft_strlen(old);
	res = (char *)malloc(i + new_sz + ft_strlen(dst + i + old_sz) + 1);
	ft_strlcpy(res, dst, i + 1);
	ft_strcpy(res + i, (char *)new);
	ft_strcpy(res + i + new_sz, dst + i + old_sz);
	return (res);
}

static char	*replace_field(char *field, char *replace_val)
{
	char *tmp;
	char *res;

	tmp = field;
	res = ft_strreplace(field, LRS, replace_val);
	free(tmp);
	return (res);
}

int			replace_dollar_question(t_cmd *cmd, int val)
{
	int		i;
	char	*sval;

	if ((sval = ft_itoa(val)) == NULL)
		return (1);
	if (cmd->command)
		cmd->command = replace_field(cmd->command, sval);
	if (cmd->file_in)
		cmd->file_in = replace_field(cmd->file_in, sval);
	if (cmd->file_out)
		cmd->file_out = replace_field(cmd->file_out, sval);
	i = 0;
	while (cmd->args[i])
	{
		if ((cmd->args[i] = replace_field(cmd->args[i], sval)) == NULL)
			return (1);
		i++;
	}
	return (!cmd->command || !cmd->file_in || !cmd->file_out);
}

/*
** Returns:
**			if is command: 1, if is file: 0 else: -1
*/

int			is_true_cmd(t_cmd *cmd)
{
	if (cmd && cmd->command[0] != 0 && cmd->args[0][0] != 0)
		return (1);
	else if (cmd && cmd->command[0] != 0 && cmd->args[0][0] == 0 \
			&& (cmd->file_in || cmd->file_out))
		return (0);
	else
		return (-1);
}
