/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 23:01:59 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/02 19:50:50 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*newcmd(void)
{
	return (ft_calloc(1, sizeof(t_cmd)));
}

void	delcmd(void *command)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = (t_cmd *)command;
	if (cmd)
	{
		if (cmd->command)
			free(cmd->command);
		if (cmd->file_in)
			free(cmd->file_in);
		if (cmd->file_out)
			free(cmd->file_out);
		if (cmd->args)
		{
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		free(cmd);
	}
}
