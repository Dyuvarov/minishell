/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abs_path_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:25:17 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/31 14:30:33 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define IS_ABSDIR(p) ((p)[0] == '/')
#define IS_CURDIR(p) ((p)[0] == '.' && (p)[1] == '/')
#define IS_PARDIR(p) ((p)[0] == '.' && (p)[1] == '.' && (p)[2] == '/')
#define IS_PATH(p) (ft_strchr((p), '/') != NULL)
#define IS_EQUAL(s1, s2) (ft_strncmp((s1), (s2), ft_strlen(s1)) == 0)

static char		*file_in_path(char *command, char **envpath)
{
	int				i;
	DIR				*cur_dir;
	struct dirent	*entry;

	i = 0;
	while (envpath[i])
	{
		cur_dir = opendir(envpath[i]);
		if (cur_dir)
		{
			errno = 0;
			while ((entry = readdir(cur_dir)) != NULL \
					&& !IS_EQUAL(entry->d_name, command))
				;
			closedir(cur_dir);
			if (entry != NULL)
				return (get_abs_path(envpath[i], command));
			else if (errno != 0)
				return (NULL);
		}
		else
			return (NULL);
		++i;
	}
	return (NULL);
}

static char		*join_path(char *p1, char *p2, size_t p2_end)
{
	char *newp;

	p2[p2_end] = '\0';
	if (p2[0] == '/')
		newp = ft_strjoin(p1, p2);
	else
		newp = get_abs_path(p1, p2);
	p2[p2_end] = '/';
	return (newp);
}

static int		init_abs_path(char *cmd, char *cdir, char **abs_path)
{
	char *tmp;

	if (IS_ABSDIR(cmd))
	{
		*abs_path = ft_strdup("");
		return (1);
	}
	else if (IS_PARDIR(cmd))
	{
		tmp = ft_strrchr(cdir, '/');
		*abs_path = join_path("", cdir, tmp - cdir);
		return (3);
	}
	else if (IS_CURDIR(cmd))
	{
		*abs_path = ft_strdup(cdir);
		return (2);
	}
	else
	{
		tmp = ft_strchr(cmd, '/');
		*abs_path = join_path(cdir, cmd, tmp - cmd);
		return (tmp - cmd + 1);
	}
}

static char		*parse_part_of_path(char *cmd, char **path)
{
	char *tmp;
	char *tmp2;

	if (IS_PARDIR(cmd))
	{
		if ((tmp = ft_strrchr(*path, '/')) != NULL)
			(*path)[tmp - *path] = '\0';
		return (cmd + 3);
	}
	else if (IS_CURDIR(cmd))
		return (cmd + 2);
	else
	{
		tmp = ft_strchr(cmd, '/');
		tmp2 = *path;
		if (tmp)
			*path = join_path(*path, cmd, tmp - cmd);
		else
			*path = get_abs_path(*path, cmd);
		free(tmp2);
		return (tmp ? tmp + 1 : 0);
	}
}

char			*get_abs_path_command(char *cmd, char **envpath)
{
	char	*cdir;
	char	*abs_path;

	cdir = get_cur_path();
	if (!cmd || !cdir || !envpath)
		return (NULL);
	if (IS_PATH(cmd))
	{
		cmd += init_abs_path(cmd, cdir, &abs_path);
		while (cmd && abs_path)
			cmd = parse_part_of_path(cmd, &abs_path);
	}
	else
	{
		errno = 0;
		if ((abs_path = file_in_path(cmd, envpath)) == NULL && \
				(errno == 0 || errno == ENOENT))
			abs_path = get_abs_path(cdir, cmd);
	}
	free(cdir);
	return (abs_path);
}
