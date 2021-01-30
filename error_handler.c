/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugreyiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:25:49 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/01/28 12:25:50 by ugreyiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


static void show_error_message(const char *command, const char *message)
{
	char *str;
	char *str_tmp;

	str = create_error_message(command);
	str_tmp = str;
	str = ft_strjoin(str, message);
	free(str_tmp);
	ft_putstr_fd(str, 1);
	free(str);
}

void handle_error(int code, const char *command)
{
	if (code == WRONG_COMMAND)
		show_error_message(command,"command not found\n");
	else if (code == MANY_ARGS)
		show_error_message(command, "too many arguments\n");
	else if (code == MALLOC_ERROR)
		show_error_message(command, "memory allocation error\n");
}