/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:13:34 by fmoaney           #+#    #+#             */
/*   Updated: 2021/01/31 18:02:16 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <string.h>

typedef struct envvar
{
	char **path;
}				s_envvar;

void parse_envp(char **envp, s_envvar *envvar)
{
	int i;


	i = 0;
	envvar->path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			envvar->path = ft_split(envp[i] + 5, ':');
		++i;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	printf("COMMAND: |%s|\n\t", cmd->command);
	printf("FILE_IN: |%s|\t FILE_OUT: |%s|\t PIPE: |%d|\t APPEND: |%d|\n\t", cmd->file_in, cmd->file_out, cmd->fl_pipe, cmd->fl_append);
	printf("ARGS:\n");
	while (cmd->args[i])
	{
		printf("\t\t%d) |%s|\n", i, cmd->args[i]);
		i++;
	}
	delcmd(cmd);
}

char		*cmd_as_line(t_cmd *cmd)
{
	int i;
	int n;
	static char buf[1000];

	i = 0;
	//n = sprintf(buf, "%s %s %s %d %d", cmd->command, cmd->file_in, cmd->file_out, cmd->fl_pipe, cmd->fl_append);
	//buf[n] = '\0';
	printf("\n|args == NULL: %d, args[i] == NULL: %d i: %d|\n", cmd->args == NULL, cmd->args[i] == NULL, i);
	while (cmd->args && cmd->args[i])
	{
		strcat(buf, " ");
		strcat(buf, cmd->args[i]);
		i++;
	}
	(void)n;
	return (buf);
}

int		checker(FILE *fp, t_cmd *cmd)
{
	int n;
	char buf[1000];

	n = fprintf(fp, "%s\n", buf);
	return (ft_strncmp(buf, cmd_as_line(cmd), n - 1));
}

void	save_in_file(FILE *fp2, int fd, t_cmd *cmd)
{
	int r;


	//r = checker(fp2, cmd);
	
	printf("\n|CORRECT ?\n|");
	r = ft_getch();
	ft_putendl_fd(cmd_as_line(cmd), fd);
	ft_putendl_fd("her", 1);
	ft_putchar_fd((char)r + '0', fd);
	ft_putendl_fd("", fd);
	(void)fp2;
}

void	print_line(int n)
{
	int c;
	int i;

	i = 0;
	printf("%d) LINE: |", n);
	while ((c = ft_getch()) != '\n' && c > 0)
	{
		i++;
		printf("%c", c);
	}
	printf("|\n");
	while (i-- >= 0)
		ft_ungetch();
}

char **copy_env(char **env)
{
	int sz;
	char **cp;

	sz = get_size(env);
	printf("%d\n", sz);
	cp = (char **)malloc(sizeof(char *) * (sz + 1));
	cp[sz] = NULL;
	while (--sz >= 0)
		cp[sz] = ft_strdup(env[sz]);
	return (cp);
}

int	main (int argc, char *argv[], char *env[])
{
	int			i;
	int			n;
	int			counter;
	char		**cp;
	t_cmd		**cmd;
	s_envvar	*envv;

	i = 0;
	envv = (s_envvar *)malloc(sizeof(s_envvar));
	cp = copy_env(env);
	parse_envp(env, envv);
	printf("ENV: \n");
	ft_env(cp);
	printf("\nPWD: \n");
	ft_pwd();
	printf("\n\n");
	counter = 0;
	while (ft_getch() > 0)
	{
		i = 0;
		ft_ungetch();
		counter++;
		increase_shlvl(cp);
		printf("ENV: \n");
		ft_env(cp);
		print_line(counter);
		if ((cmd = parse_cmd_line(env, envv->path)) == NULL)
		{
			printf("ERROR!\n\n");
			while ((n = ft_getch()) != '\n')
				;
		}
		set_last_red_file(cmd);
		while (cmd && cmd[i])
		{
			print_cmd(cmd[i]);
			i++;
		}
		free(cmd);
	}
	i = 0;
	while (envv->path[i])
		free(envv->path[i++]);
	i = 0;
	while (cp[i])
		free(cp[i++]);
	free(cp);
	free(envv->path);
	free(envv);
	(void)argc;
	(void)argv;
}
