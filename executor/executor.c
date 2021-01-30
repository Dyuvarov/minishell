/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:32:37 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/01/25 10:32:39 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "string.h"
#include "errno.h"
#include "fcntl.h"

void execute_no_redirection(t_cmd *command, char **envp, int tmp_fd[])
{
	int exec_ret;
	int pid;
	int status;

	status = 0;
	if (command->args[0])
	{
		pid = fork();
		if (pid == 0)
		{
			exec_ret = execve(command->args[0], command->args, envp);
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
	else
		handle_error(WRONG_COMMAND, command->command);
}

void execute_with_pipe(t_cmd *command, char **envp)
{
	int exec_ret;
	int pid;
	int status;

	status = 0;
	if (command->args[0])
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(command->fd[1], 1);
			close(command->fd[0]);
			exec_ret = execve(command->args[0], command->args, envp);
			if (exec_ret < 0)
				handle_error(WRONG_COMMAND, command->command);
			close(command->fd[1]);
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
	else
		handle_error(WRONG_COMMAND, command->command);
}

void execute_with_in_redirection(t_cmd *command, char **envp)
{
	int exec_ret;
	int pid;
	int status;

	command->fd[1] = open(command->file_in, O_CREAT | O_RDWR | O_TRUNC, 0666);
	status = 0;
	if (command->args[0])
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(command->fd[1], 1);
			exec_ret = execve(command->args[0], command->args, envp);
			if (exec_ret < 0)
				handle_error(WRONG_COMMAND, command->command);
			close(command->fd[1]);
			exit(0);
		}
		else if(pid < 0)
			exit(1); //fork error
		else
		{
			close(command->fd[1]);
			wait(&status);
		}
	}
	else
		handle_error(WRONG_COMMAND, command->command);
}

void execute_with_out_redirection(t_cmd *command, char **envp)
{
	int exec_ret;
	int pid;
	int status;

	command->fd[0] = open(command->file_out, O_RDONLY);
	status = 0;
	if (command->args[0])
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(command->fd[0], 0);
			exec_ret = execve(command->args[0], command->args, envp);
			if (exec_ret < 0)
				handle_error(WRONG_COMMAND, command->command);
			close(command->fd[0]);
			exit(0);
		}
		else if(pid < 0)
			exit(1); //fork error
		else
		{
			close(command->fd[0]);
			wait(&status);
		}
	}
	else
		handle_error(WRONG_COMMAND, command->command);
}

void execute_command(t_cmd *cmd, char **envp, int tmp_fd[])
{
	if (cmd->fl_pipe)
	{
		pipe(cmd->fd);
		execute_with_pipe(cmd, envp);
	}
	else if (cmd->file_in)
		execute_with_in_redirection(cmd, envp);
	else if (cmd->file_out)
		execute_with_out_redirection(cmd, envp);
	else
		execute_no_redirection(cmd, envp, tmp_fd);
}

int execute_cd(char *new_path, char **envp)
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

void executor(t_cmd *cmd, char **envp, int tmp_fd[])
{
	char **args;

	args = cmd->args + 1;
	if (ft_strncmp(cmd->command, "cd", ft_strlen(cmd->command)) == 0)
		execute_cd(cmd->args[1], envp);
	else if (ft_strncmp(cmd->command, "echo", ft_strlen(cmd->command)) == 0)
		ft_echo(args);
	else if (ft_strncmp(cmd->command, "env", ft_strlen(cmd->command)) == 0)
		ft_env(envp);
	else if (ft_strncmp(cmd->command, "export", ft_strlen(cmd->command)) == 0)
		ft_export(args, &envp);
	else if (ft_strncmp(cmd->command, "pwd", ft_strlen(cmd->command)) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->command, "unset", ft_strlen(cmd->command)) == 0)
		ft_unset(args, &envp);
	else if (ft_strncmp(cmd->command, "exit", ft_strlen(cmd->command)) == 0)
		ft_exit(args);
	else
		execute_command(cmd, envp, tmp_fd);
}

