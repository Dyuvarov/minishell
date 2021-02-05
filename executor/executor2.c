/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:56:58 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/05 12:57:41 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		execute_cd(char *new_path)
{
	int		res;

	res = chdir(new_path);
	if (res < 0)
		handle_cd_error(new_path);
	return (res < 0 ? errno : 0);
}

void	execute_export(t_cmd *cmd, char ***env, t_tools *tools)
{
	extern int g_last_res;

	if (cmd->file_in)
	{
		cmd->fd[1] = open(cmd->file_in, O_CREAT | O_RDWR | \
				(cmd->fl_append ? O_APPEND : O_TRUNC), 0666);
		if (cmd->fd[1] < 0)
		{
			handle_error(FD_ERROR, cmd->file_in);
			return ;
		}
		dup2(cmd->fd[1], 1);
		close(cmd->fd[1]);
	}
	g_last_res = ft_export(cmd->args + 1, env);
	if (cmd->file_in)
		dup2(tools->tmp_fd[1], 1);
}
