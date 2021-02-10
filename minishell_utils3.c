/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:06:26 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/10 21:28:47 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	size_t	i;
	size_t	j;
	size_t	size;
	char	*temp;

	size = get_size(strs);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(strs[j], strs[j + 1], ft_strlen(strs[j])) > 0)
			{
				temp = strs[j];
				strs[j] = strs[j + 1];
				strs[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char			*replace_new_env(char *field, char **env)
{
	int		start;
	int		end;
	char	*val;
	char	*tmp;
	char	*res;

	if ((start = ft_indexof(field, ENV_MARK, 0)) == -1)
		return (ft_strdup(field));
	if ((end = ft_indexof(field, ENV_MARK, start + 1)) == -1)
		return (ft_strdup(field));
	field[end] = '\0';
	val = get_env_var(field + start + ft_strlen(ENV_MARK), env);
	val = val ? val : "";
	field[start] = '\0';
	if ((tmp = ft_strjoin(field, val)) == NULL)
		return (NULL);
	res = ft_strjoin(tmp, field + end + ft_strlen(ENV_MARK));
	free(tmp);
	return (res);
}

void			**ft_join_dpoiner(void **dp1, void **dp2)
{
	int		i;
	int		sz;
	void	**res;

	i = 0;
	sz = get_size((char **)dp1) + get_size((char **)dp2) + 1;
	if ((res = (void **)malloc(sizeof(void *) * sz)) == NULL)
		return (NULL);
	while (*dp1)
		res[i++] = *dp1++;
	while (*dp2)
		res[i++] = *dp2++;
	res[i] = NULL;
	return (res);
}

int				repair_command(t_cmd *cmd)
{
	char		*tmp;
	char		**tmp_dp;
	char		**splt;

	if ((splt = ft_split(cmd->command, ' ')) && splt[1])
	{
		free(cmd->command);
		cmd->command = splt[0];
		tmp = cmd->args[0];
		cmd->args[0] = splt[1];
		splt[1] = tmp;
		tmp_dp = cmd->args;
		cmd->args = (char **)ft_join_dpoiner(\
				(void **)(splt + 1), (void **)cmd->args);
		free(tmp_dp);
	}
	else if (splt)
		free(splt[0]);
	free(splt);
	if (!splt || !cmd->args)
		return (1);
	return (0);
}
