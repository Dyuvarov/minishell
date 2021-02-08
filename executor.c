/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:32:37 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/08 19:14:31 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"


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
		exec_ret = ft_env(args, envp);
	else if (ft_strequal(cmd->command, "pwd"))
		exec_ret = ft_pwd();
	else
		if ((exec_ret = execve(cmd->args[0], cmd->args, envp)) < 0)
		{
			exec_ret = 127;
			handle_error(WRONG_COMMAND, cmd->command);
		}
	return (exec_ret);
}

void	execute_no_redirection(t_cmd *command, char **envp, int tmp_fd[])
{
	int			exec_ret;
	int			pid;
	int			status;
	extern int	g_last_res;

	pid = fork();
	if (pid == 0)
	{
		exec_ret = call_func(command, envp);
		exit(exec_ret);
	}
	else if (pid < 0)
		exit(1);
	else
	{
		dup2(tmp_fd[0], 0);
		dup2(tmp_fd[1], 1);
		waitpid(pid, &status, WUNTRACED);
		if (WTERMSIG(status))
			g_last_res = 130;
		else
			g_last_res = WEXITSTATUS(status);
	}
}

void	execute_with_pipe(t_cmd *command, char **envp)
{
	int			exec_ret;
	int			pid;
	int			status;
	extern int	g_last_res;

	pid = fork();
	if (pid == 0)
	{
		dup2(command->fd[1], 1);
		close(command->fd[0]);
		exec_ret = call_func(command, envp);
		close(command->fd[1]);
		exit(exec_ret);
	}
	else if (pid < 0)
		exit(1);
	else
	{
		dup2(command->fd[0], 0);
		close(command->fd[1]);
		waitpid(pid, &status, WUNTRACED);
		close(command->fd[0]);
		if (WTERMSIG(status))
			g_last_res = 130;
		else
			g_last_res = WEXITSTATUS(status);
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
	if (cmd->file_out)
	{
		if ((cmd->fd[0] = open(cmd->file_out, O_RDONLY)) < 0)
		{
			handle_error(FD_ERROR, cmd->file_out);
			dup2(tmp_fd[1], 1);
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
	if (cmd->fl_pipe)
		g_prepipe = 1;
	if ((ft_strequal(cmd->command, "cd")	\
	|| ft_strequal(cmd->command, "exit")	\
	|| ft_strequal(cmd->command, "export")	\
	|| ft_strequal(cmd->command, "unset")) && !g_prepipe && !(cmd->fl_pipe))
		execute_in_current_process(cmd, envp, tools);
	else if (cmd->file_in || cmd->file_out)
		execute_with_redirection(cmd, *envp, tools->tmp_fd);
	else if (cmd->fl_pipe)
	{
		pipe(cmd->fd);
		execute_with_pipe(cmd, *envp);
	}	
	else
		execute_no_redirection(cmd, *envp, tools->tmp_fd);
	if (!(cmd->fl_pipe))	
		g_prepipe = 0 ;
}