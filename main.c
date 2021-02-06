/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 12:25:47 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/06 18:34:32 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

static char		**clone_envp(char **envp)
{
	char	**envtmp;
	int		i;
	int		len;

	i = 0;
	while (envp[i])
		++i;
	len = i;
	if (!(envtmp = (char **)malloc(sizeof(char *) * len)))
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

static void		prepare_to_work(t_tools **tools, char ***clone_env, \
		char **envp, void *unused)
{
	if (!(*tools = malloc(sizeof(t_tools))))
	{
		handle_error(MALLOC_ERROR, "minishell");
		exit(ENOMEM);
	}
	(*tools)->tmp_fd[0] = dup(0);
	(*tools)->tmp_fd[1] = dup(1);
	if (!(*clone_env = clone_envp(envp)))
	{
		handle_error(MALLOC_ERROR, "minishell");
		exit(ENOMEM);
	}
	increase_shlvl(get_env_var("SHLVL", *clone_env), clone_env);
	(void)unused;
}

static void		set_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void			show_promt(void)
{
	write(1, G_PRESTR, ft_strlen(G_PRESTR));
}

int				main(int argc, char **argv, char **envp)
{
	t_cmd		**cmd;
	t_tools		*tools;
	char		**envtmp;
	int			i;
	extern int	g_last_res;

	prepare_to_work(&tools, &envtmp, envp, argv[argc]);
	while (1)
	{
		set_signal();
		show_promt();
		if ((cmd = parse_cmd_line(envtmp)) == NULL)
			minishell_exit();
		if ((cmd[0]->command[0] != 0 || cmd[1]) && !set_last_red_file(cmd))
		{
			i = -1;
			while (cmd[++i])
			{
				replace_dollar_question(cmd[i], g_last_res);
				executor(cmd[i], &envtmp, tools);
			}
		}
		free_cmd(cmd);
	}
	return (0);
}
