/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:32:37 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/03 15:16:12 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "string.h"
#include "errno.h"
#include "fcntl.h"

int execute_cd(char *new_path)
{
	int		res;
	char	*err_str;
	char 	*err_tmp;

	res = chdir(new_path);
	if (res < 0)
	{
		err_str = ft_strjoin("minishell: cd : ", new_path);
		err_tmp = err_str;
		err_str = ft_strjoin(err_str, ": ");
		free(err_tmp);
		err_tmp = err_str;
		err_str = ft_strjoin(err_str, strerror(errno));
		free(err_tmp);
		err_tmp = err_str;
		err_str = ft_strjoin(err_str, "\n");
		free(err_tmp);
		write(1, err_str, ft_strlen(err_str));
		free(err_str);
	}
	return (0);
}

int	call_func(t_cmd *cmd, char ** envp)
{
	char **args;
	int		exec_ret;

	args = cmd->args + 1;
	if (ft_strncmp(cmd->command, "echo", ft_strlen(cmd->command)) == 0)
		exec_ret = ft_echo(args);
	else if (ft_strncmp(cmd->command, "env", ft_strlen(cmd->command)) == 0)
		exec_ret = ft_env(envp);
	else if (ft_strncmp(cmd->command, "export", ft_strlen(cmd->command)) == 0)
		exec_ret = ft_export(args, &envp);
	
	else if (ft_strncmp(cmd->command, "pwd", ft_strlen(cmd->command)) == 0)
		exec_ret = ft_pwd();
	else
		exec_ret = execve(cmd->args[0], cmd->args, envp);

	return (exec_ret);
}

void execute_no_redirection(t_cmd *command, char **envp, int tmp_fd[])
{
	int exec_ret;
	int	pid;
	int status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		exec_ret = call_func(command, envp);
		if (exec_ret < 0)
			handle_error(WRONG_COMMAND, command->command);
		exit(0);
	}
	else if(pid < 0)
		exit(1); //fork error
	else
	{
		dup2(tmp_fd[0], 0);
		dup2(tmp_fd[1], 1);
		wait(&status);
	}
}

void execute_with_pipe(t_cmd *command, char **envp)
{
	int exec_ret;
	int pid;
	int status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		dup2(command->fd[1], 1);
		close(command->fd[0]);
		exec_ret = call_func(command, envp);
		close(command->fd[1]);
		if (exec_ret < 0)
			handle_error(WRONG_COMMAND, command->command);
		exit(0);
	}
	else if(pid < 0)
		exit(1); //fork error
	else
	{
		dup2(command->fd[0],0);
		close(command->fd[1]);
		wait(&status);
		close(command->fd[0]);
	}
}

void execute_with_redirection(t_cmd *cmd, char **envp, int tmp_fd[])
{
	if (cmd->file_in)
	{
		if (cmd->fl_append)
			cmd->fd[1] = open(cmd->file_in, O_CREAT | O_RDWR | O_APPEND, 0666);
		else
			cmd->fd[1] = open(cmd->file_in, O_CREAT | O_RDWR | O_TRUNC, 0666);
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
		cmd->fd[0] = open(cmd->file_out, O_RDONLY);
		if (cmd->fd[0] < 0)
		{
			handle_error(FD_ERROR, cmd->file_out);
			return ;
		}
		dup2(cmd->fd[0], 0);
		close(cmd->fd[0]);
	}
	execute_no_redirection(cmd, envp, tmp_fd);
}

void executor(t_cmd *cmd, char **envp, int tmp_fd[])
{
	char **args;

	args = cmd->args + 1;
	if (ft_strncmp(cmd->command, "cd", ft_strlen(cmd->command)) == 0)
	{
		execute_cd(cmd->args[1]);
		return ;
	}
	else if (ft_strncmp(cmd->command, "unset", ft_strlen(cmd->command)) == 0)
	{
		ft_unset(args, &envp);
		return ;
	}
	else if (ft_strncmp(cmd->command, "exit", ft_strlen(cmd->command)) == 0)
	{
		ft_exit(args);
		return ;
	}	
	if (cmd->fl_pipe)
	{
		pipe(cmd->fd);
		execute_with_pipe(cmd, envp);
	}
	else if (cmd->file_in || cmd->file_out)
		execute_with_redirection(cmd, envp, tmp_fd);
	else
		execute_no_redirection(cmd, envp, tmp_fd);
}


