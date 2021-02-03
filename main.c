#include "libft.h"
#include <zconf.h>
#include "minishell.h"
#include "executor/executor.h"

void parse_PATH(char **envp, s_tools *tools)
{
	int i;
	char *tmp;

	i = 0;
	tools->path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			tmp = envp[i] + 5;
			tools->path = ft_split(tmp, ':');
		}
		++i;
	}
	tools->tmp_fd[0] = dup(0);
	tools->tmp_fd[1] = dup(1);
}

char **clone_envp(char **envp)
{
	char **envtmp;
	int i;
	int len;

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

void show_promt()
{
	write(1, G_PRESTR, ft_strlen(G_PRESTR));	
}

int main(int argc, char **argv, char **envp)
{
	t_cmd		**cmd;
	s_tools		*tools;
	char		**envtmp;
	char 		*shlvl;
	int			i;

	(void)argc;
	(void)argv;
	if (!(tools = malloc(sizeof(s_tools))))
		handle_error(MALLOC_ERROR, "minishell");
	parse_PATH(envp, tools);
	if (!(envtmp = clone_envp(envp)))
		handle_error(MALLOC_ERROR, "minishell");
	shlvl = get_env_var("SHLVL", envtmp);
	increase_shlvl(shlvl, &envtmp);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		show_promt();
		cmd = parse_cmd_line(envtmp, tools->path);
		if (!cmd)
			minishell_exit();
		if (cmd && (ft_strlen(cmd[0]->command) > 0))
		{
			set_last_red_file(cmd);
			i = 0;
			while (cmd[i])
			{
				executor(cmd[i], &envtmp, tools);
				++i;
			}
		}
		free_cmd(cmd);
	}
	return 0;
}


