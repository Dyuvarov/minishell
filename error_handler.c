/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:25:49 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/07 17:39:54 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

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
	char 		*slash;
	extern int g_last_res;

	if (code == WRONG_COMMAND)
	{
		if (!(slash = ft_strrchr(command, '/')))
			show_error_message(command, "command not found");
		else if (*(slash + 1) != '\0')
			show_error_message(command, "No such file or directory");
		else
			show_error_message(command, "is a directory");
	}
	else if (code == MANY_ARGS)
		show_error_message(command, "too many arguments");
	else if (code == MALLOC_ERROR)
		show_error_message(command, strerror(errno));
	else if (code == FD_ERROR)
		show_error_message(command, strerror(errno));
	g_last_res = errno;
	return (-1);
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
