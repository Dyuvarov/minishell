/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:07:04 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/02 19:45:51 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define IS_SYSERR(stdin_c, alloc_mem) (((stdin_c) < 1) || (alloc_mem) == NULL)

/*
** Parse cmd arguments until meets '\n', '<', '>' or '|'
**
** Returns the last char read back to stdin buffer (ft_ungetch())
**
** Uses "safe_realloc" function to control occupancy and dynamic realloc
**
** Returns: parsed NULL-terminated array_of_args or NULL (if ERROR or EOF)
*/

static char		**parse_args(char *command, char **env, char **envpath)
{
	int		i;
	int		c;
	char	**args;

	i = 0;
	if (!(args = (char **)malloc(sizeof(char *) * BUFFER_SIZE)))
		return (NULL);
	args[i] = get_abs_path_command(command, envpath);
	while (args[i++] && !skip_spaces() \
			&& (c = ft_getch()) > 0 \
			&& !ft_strchr(SPEC_CHARS, c))
	{
		ft_ungetch();
		if ((args = safe_realloc(args, i, sizeof(*args))) == NULL)
			return (NULL);
		args[i] = parse_seq(env);
	}
	if (IS_SYSERR(c, args[i - 1]) || !ft_strchr(SPEC_CHARS, c))
		free_dpointer((void ***)&args, i != 0 && !args[i - 1] ? i - 1 : i);
	else
	{
		args = normalize_arr(args, i, sizeof(*args));
		ft_ungetch();
	}
	return (args);
}

static int		skip_pipe_n_semicolon(void)
{
	int c;
	int err;

	err = skip_spaces();
	if ((c = ft_getch()) > 0 && c != '|' && c != ';')
		ft_ungetch();
	return (err || c < 1);
}

static int		parse_filename(t_cmd *cmd, int is_out, char **env)
{
	int		c;
	char	**file;

	c = 1;
	if (is_out && (c = ft_getch()) > 0)
	{
		if (c == '>')
			cmd->fl_append = 1;
		else
			ft_ungetch();
		file = &cmd->file_in;
	}
	else
		file = &cmd->file_out;
	return (c < 1								\
			|| skip_spaces()					\
			|| (*file = parse_seq(env)) == NULL	\
			|| skip_pipe_n_semicolon());
}

/*
** Parse and create cmd (type of t_cmd)
**
** If the last char == '\n', returns it back to stdin buffer (ft_ungetch())
**
** Returns: parsed cmd or NULL (if ERROR or EOF)
*/

static t_cmd	*parse_cmd(char **env, char **envpath)
{
	int		c;
	int		err;
	t_cmd	*cmd;

	if (skip_spaces() || (cmd = newcmd()) == NULL)
		return (NULL);
	err = 0;
	if ((cmd->command = parse_seq(env)))
		if ((cmd->args = parse_args(cmd->command, env, envpath)))
			if ((c = ft_getch()) > 0)
			{
				if (c == '<' || c == '>')
					err = parse_filename(cmd, c == '>', env);
				else if (c == '\n')
					ft_ungetch();
				cmd->fl_pipe = c == '|';
			}
	if (!cmd->command || !cmd->args || c < 1 || err)
	{
		delcmd(cmd);
		return (NULL);
	}
	return (cmd);
}

/*
** ---Main parsing function---
**
** Read from stdin and parse command_line until meets '\n'
**
** Uses the construction like "do while"
**
** Uses "safe_realloc" function to control occupancy and dynamic realloc
**
** Returns: parsed command lines or NULL (if ERROR or EOF)
*/

t_cmd			**parse_cmd_line(char **env, char **envpath)
{
	int		i;
	int		c;
	t_cmd	**res;

	i = 0;
	if ((res = (t_cmd **)malloc(sizeof(t_cmd *) * BUFFER_SIZE)) == NULL)
		return (NULL);
	res[i] = parse_cmd(env, envpath);
	while (res[i++] != NULL && (c = ft_getch()) > 0 && c != '\n')
	{
		ft_ungetch();
		if ((res = safe_realloc(res, i, sizeof(*res))) == NULL)
			return (NULL);
		res[i] = parse_cmd(env, envpath);
	}
	if (IS_SYSERR(c, res[i - 1]))
		free_dpointer((void ***)&res, i != 0 && !res[i - 1] ? i - 1 : i);
	else
		res = (t_cmd **)normalize_arr(res, i, sizeof(*res));
	return (res);
}
