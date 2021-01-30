#ifndef EXECUTER_H
# define EXECUTER_H

# include <dirent.h>
# include "minishell.h"

# define WRONG_COMMAND 1
# define MANY_ARGS 2
# define MALLOC_ERROR 3

typedef struct envvar
{
	char **path;
	int tmp_fd[2];
}				s_envvar;

void	handle_error(int code, const char *command);
void	executor(t_cmd *cmd, char **envp, int tmp_fd[]);
int		free_dpointer_no_size(void **p);
#endif
