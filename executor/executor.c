/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:32:37 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/07 10:34:37 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/executor.h"

int		call_func(t_cmd *cmd, char **envp)
{
	char	**args;
	int		exec_ret;

	args = cmd->args + 1;
	if (ft_strequal(cmd->command, "echo"))
		exec_ret = ft_echo(args);
	else if (ft_strequal(cmd->command, "cd"))
		exec_ret = execute_cd(*args);
	else if (ft_strequal(cmd->command, "unset"))
		exec_ret = ft_unset(args, &envp);
	else if (ft_strequal(cmd->command, "exit"))
		exec_ret = ft_exit(args);
	else if (ft_strequal(cmd->command, "export"))
		exec_ret = ft_export(args, &envp);
	else if (ft_strequal(cmd->command, "env"))
		exec_ret = ft_env(envp);
	else if (ft_strequal(cmd->command, "pwd"))
		exec_ret = ft_pwd();
	else
		exec_ret = execve(cmd->args[0], cmd->args, envp);
	return (exec_ret);
}

void	execute_no_redirection(t_cmd *command, char **envp, int tmp_fd[])
{
	int			exec_ret;
	int			pid;
	extern int	g_last_res;

	pid = fork();
	if (pid == 0)
	{
		exec_ret = call_func(command, envp);
		if (exec_ret < 0)
			handle_error(WRONG_COMMAND, command->command);
		exit(exec_ret);
	}
	else if (pid < 0)
		exit(1);
	else
	{
		dup2(tmp_fd[0], 0);
		dup2(tmp_fd[1], 1);
		wait(&pid);
		g_last_res = WEXITSTATUS(pid);
	}
}

void	execute_with_pipe(t_cmd *command, char **envp)
{
	int			exec_ret;
	int			pid;
	extern int	g_last_res;

	pid = fork();
	if (pid == 0)
	{
		dup2(command->fd[1], 1);
		close(command->fd[0]);
		exec_ret = call_func(command, envp);
		close(command->fd[1]);
		if (exec_ret < 0)
			handle_error(WRONG_COMMAND, command->command);
		exit(exec_ret);
	}
	else if (pid < 0)
		exit(1);
	else
	{
		dup2(command->fd[0], 0);
		close(command->fd[1]);
		wait(&pid);
		close(command->fd[0]);
		g_last_res = WEXITSTATUS(pid);
	}
}

void	execute_with_redirection(t_cmd *cmd, char **envp, int tmp_fd[])
{
	if (cmd->file_in)
	{
		cmd->fd[1] = open(cmd->file_in, O_CREAT | O_RDWR \
				| (cmd->fl_append ? O_APPEND : O_TRUNC), 0666);
		if (cmd->fd[1] < 0)
		{
			handle_error(FD_ERROR, cmd->file_in);
			return ;
		}
		dup2(cmd->fd[1], 1);
		close(cmd->fd[1]);
	}
	else
	{
		if ((cmd->fd[0] = open(cmd->file_out, O_RDONLY)) < 0)
		{
			handle_error(FD_ERROR, cmd->file_out);
			return ;
		}
		dup2(cmd->fd[0], 0);
		close(cmd->fd[0]);
	}
	execute_no_redirection(cmd, envp, tmp_fd);
}

void	executor(t_cmd *cmd, char ***envp, t_tools *tools)
{
	char		**args;
	extern int	g_last_res;

	signal(SIGINT, input_signal_handler);
	signal(SIGQUIT, input_signal_handler);
	args = cmd->args + 1;
	if (!cmd->fl_pipe && ft_strequal(cmd->command, "cd"))
		g_last_res = execute_cd(*args);
	else if (!cmd->fl_pipe && ft_strequal(cmd->command, "unset"))
		g_last_res = ft_unset(args, envp);
	else if (!cmd->fl_pipe && ft_strequal(cmd->command, "export"))
		execute_export(cmd, envp, tools);
	else if (!cmd->fl_pipe && ft_strequal(cmd->command, "exit"))
		g_last_res = ft_exit(args);
	else if (cmd->fl_pipe)
	{
		pipe(cmd->fd);
		execute_with_pipe(cmd, *envp);
	}
	else if (cmd->file_in || cmd->file_out)
		execute_with_redirection(cmd, *envp, tools->tmp_fd);
	else
		execute_no_redirection(cmd, *envp, tools->tmp_fd);
}
