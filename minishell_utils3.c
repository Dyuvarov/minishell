/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:06:26 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/10 15:39:41 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

char			**clone_envp(char **envp)
{
	char	**envtmp;
	int		i;
	int		len;

	i = 0;
	while (envp[i])
		++i;
	len = i;
	if (!(envtmp = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (!(envtmp[i] = ft_strdup(envp[i])))
		{
			free_dpointer_no_size((void **)envtmp);
			return (NULL);
		}
		++i;
	}
	envtmp[i] = NULL;
	return (envtmp);
}

void			bubblesort(char **strs)
{
	size_t i;
	size_t j;
	size_t size;

	size = get_size(strs);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(strs[j], strs[j + 1], ft_strlen(strs[j])) > 0)
				swap(strs, j, j + 1);
			j++;
		}
		i++;
	}
}
