/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:56:58 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/07 15:44:12 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int     execute_cd(char *new_path)
{
    int     res;
	if (!new_path)
		return (0);
    res = chdir(new_path);
    if (res < 0)
        handle_cd_error(new_path);
    return (res < 0 ? errno : 0);
}

void	execute_in_current_process(t_cmd *cmd, char ***env, t_tools *tools)
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
	if (ft_strequal(cmd->command, "cd"))
		g_last_res = execute_cd(cmd->args[1]);
	else if (ft_strequal(cmd->command, "unset"))
		g_last_res = ft_unset(cmd->args + 1, env);
	else if (ft_strequal(cmd->command, "export"))
		g_last_res = ft_export(cmd->args + 1, env);
	else if (ft_strequal(cmd->command, "exit"))
		g_last_res = ft_exit(cmd->args + 1);
	if (g_last_res == ENOMEM)
		handle_error(MALLOC_ERROR, cmd->command);
	if (cmd->file_in)
		dup2(tools->tmp_fd[1], 1);
}
