/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repair_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:34:30 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/11 18:17:11 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**split_env(char *env_val, char marker)
{
	char **res;

	if (env_val == NULL)
	{
		if ((res = (char **)malloc(sizeof(char *))) == NULL)
			return (NULL);
		res[0] = NULL;
	}
	else if (marker == ENV_MWQ)
	{
		if ((res = ft_split(env_val, ' ')) == NULL)
			return (NULL);
	}
	else
	{
		if ((res = (char **)malloc(sizeof(char *) * 2)) == NULL)
			return (NULL);
		res[0] = ft_strdup(env_val);
		res[1] = NULL;
	}
	return (res);
}

static void		add_end(char **s, char c)
{
	int		sz;
	char	*new;

	sz = ft_strlen(*s);
	if ((new = (char *)malloc(sz + 2)) == NULL)
		return ;
	ft_strcpy(new, *s);
	new[sz] = c;
	new[sz + 1] = '\0';
	free(*s);
	*s = new;
}

static char		*get_env(char *f, int start, char **env)
{
	int		end;
	char	t;
	char	smarker[2];
	char	*env_val;

	smarker[0] = f[start];
	smarker[1] = '\0';
	end = ft_indexof(f + start, smarker, 1) + start;
	t = f[end];
	f[end] = 0;
	env_val = get_env_var(f + start + 1, env);
	f[end] = t;
	return (env_val);
}

static char		*join_tail(char **tail, char *new_tail, char c, char *env_val)
{
	char *tmp;

	if (c == ENV_MDQ || (env_val && !ft_isspace(env_val[0])))
	{
		tmp = *tail;
		if ((*tail = ft_strjoin(tmp, new_tail)) == NULL)
			return (NULL);
		free(tmp);
	}
	return (*tail);
}

char			*repair_field(char *f, char ***args, int *pos, char **env)
{
	int		i;
	char	*head;
	char	*env_val;
	char	**tail;
	char	**pars;

	i = 0;
	head = (char *)ft_calloc(1, sizeof(char));
	tail = &head;
	while (f[i] && head)
		if (f[i] == ENV_MWQ || f[i] == ENV_MDQ)
		{
			env_val = get_env(f, i, env);
			if ((pars = split_env(env_val, f[i])) == NULL)
				return (NULL);
			if (pars[0] && join_tail(tail, pars[0], f[i], env_val) == NULL)
				return (NULL);
			if (pars[0] != NULL && pars[1] != NULL)
			{
				*pos = ft_insert(args, pars + 1, *pos + 1) - 1;
				if (f[i] == ENV_MWQ && pars[1])
					tail = (*args) + (*pos) - 1;
			}
			free(pars[0]);
			free(pars);
			i = ft_strchr(f + i + 1, f[i]) - f + 1;
		}
		else
			add_end(tail, f[i++]);
	return (head);
}
