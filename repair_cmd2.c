/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repair_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:04:22 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/12 16:34:36 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_join(char *tail, char *env_val)
{
	return (!*tail || (env_val && !ft_isspace(*env_val)));
}

int		from0(char *tail, char *arg0, char *env_val)
{
	return (env_val && ft_isspace(*env_val) && !ft_strequal(tail, arg0));
}

int		free_tmp_splt(char **splt, int free_zero)
{
	if (free_zero)
		free(splt[0]);
	free(splt);
	return (0);
}

int		insert_new_args(char **new, char ***args_buf, int *pos,\
		int from_zero)
{
	char *copy;

	if (new[0] && from_zero)
		copy = ft_strdup(new[0]);
	if (new[0] != NULL && (new[1] != NULL || from_zero))
	{
		*pos = ft_insert(args_buf, new + !from_zero, *pos + 1) - 1;
		return (1);
	}
	if (new[0] && from_zero)
		new[0] = copy;
	return (0);
}
