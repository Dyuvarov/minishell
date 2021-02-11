/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <ugreyiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:25:49 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/11 19:49:36 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <sys/stat.h>

static char	*create_error_message(const char *command)
{
	char *str;
	char *str_tmp;

	str = ft_strjoin("minishell: ", command);
	str_tmp = str;
	str = ft_strjoin(str, ": ");
	free(str_tmp);
	return (str);
}

static void	show_error_message(const char *command, const char *message)
{
	char *str;
	char *str_tmp;

	str = create_error_message(command);
	str_tmp = str;
	str = ft_strjoin(str, message);
	free(str_tmp);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(str);
}

int			handle_error(int code, const char *command)
{
	char		*slash;
	int			ret;
	struct stat	s_inf;

	ret = 1;
	if (code == WRONG_COMMAND)
	{
		if (!(stat(command, &s_inf)))
		{
			ret = 126;
			if (S_ISDIR(s_inf.st_mode))
				show_error_message(command, "is a directory");
			else if (S_ISREG(s_inf.st_mode) && (ft_strncmp(command, "./", 2) == 0))
				show_error_message(command, "Permission denied");
			else
			{
				ret = 127;
				show_error_message(command, "command not found");
			}
		}
		else
		{
			ret = 127;
			if (!(slash = ft_strrchr(command, '/')))
				show_error_message(command, "command not found");
			else if (*(slash + 1) != '\0')
				show_error_message(command, "No such file or directory");
		}
	}
	else if (code == MANY_ARGS)
		show_error_message(command, "too many arguments");
	else if (code == MALLOC_ERROR)
		show_error_message(command, strerror(errno));
	else if (code == FD_ERROR)
		show_error_message(command, strerror(errno));
	return (ret);
}

void		handle_cd_error(char *path)
{
	char	*err_str;
	char	*err_tmp;

	err_str = ft_strjoin("minishell: cd : ", path);
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
