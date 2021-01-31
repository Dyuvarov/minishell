#include "libft.h"
#include <zconf.h>
#include "minishell.h"
#include "executor/executor.h"

void parse_PATH(char **envp, s_envvar *envvar)
{
	int i;
	char *tmp;

	i = 0;
	envvar->path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			tmp = envp[i] + 5;
			envvar->path = ft_split(tmp, ':');
		}
		++i;
	}
	envvar->tmp_fd[0] = dup(0);
	envvar->tmp_fd[1] = dup(1);
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
	s_envvar	*envvar;
	char		**envtmp;
	int			i;

	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	if (!(envvar = malloc(sizeof(s_envvar))))
		exit (1);
	parse_PATH(envp, envvar);
	envtmp = clone_envp(envp);
	while (1)
	{
		show_promt();
		cmd = parse_cmd_line(envtmp, envvar->path);
		if (!cmd)
			minishell_exit();
		if (cmd && (ft_strlen(cmd[0]->command) > 0))
		{
			set_last_red_file(cmd);
			i = 0;
			while (cmd[i])
			{
				executor(cmd[i], envtmp, envvar->tmp_fd);
				++i;
			}
		}
		free_cmd(cmd);
	}
	return 0;
}


