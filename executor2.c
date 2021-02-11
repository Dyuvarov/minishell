/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:56:58 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/11 21:10:02 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		execute_cd(char *new_path)
{
	int	res;

	if (!new_path)
		return (0);
	res = chdir(new_path);
	if (res < 0)
		handle_cd_error(new_path);
	return (res < 0 ? 1 : 0);
}

int		open_redirect(t_cmd *cmd, int direct)
{
	int err;

	if (direct == 1)
	{
		cmd->fd[1] = open(cmd->file_in, O_CREAT | O_RDWR | \
				(cmd->fl_append ? O_APPEND : O_TRUNC), 0666);
		if (cmd->fd[1] < 0)
			return (1);
		err = dup2(cmd->fd[1], 1) == -1;
		err |= close(cmd->fd[1]);
	}
	else if (direct == 0)
	{
		cmd->fd[0] = open(cmd->file_out, O_RDONLY);
		if (cmd->fd[0] < 0)
			return (1);
		err = dup2(cmd->fd[0], 0) == -1;
		err |= close(cmd->fd[0]);
	}
	else
		return (1);
	return (err);
}

void	open_empty_pipe(int tmp_fd[])
{
	pipe(tmp_fd);
	dup2(tmp_fd[0], 0);
	close(tmp_fd[0]);
	close(tmp_fd[1]);
}

int		handle_redirect(t_cmd *cmd, int tmp_fd[])
{
	if (cmd->file_in && open_redirect(cmd, 1))
	{
		handle_error(FD_ERROR, cmd->file_in);
		return (1);
	}
	if (cmd->file_out && open_redirect(cmd, 0))
	{
		handle_error(FD_ERROR, cmd->file_out);
		dup2(tmp_fd[1], 1);
		return (1);
	}
	return (0);
}

void	execute_in_current_process(t_cmd *cmd, char ***env)
{
	extern int g_last_res;

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
}
