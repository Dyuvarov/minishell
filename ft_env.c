/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:10:09 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/31 14:39:11 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **env)
{
	if (env == NULL)
		return (-1);
	while (*env)
		if (ft_putendl_fd(*env++, 1) == -1)
			return (errno);
	return (0);
}
