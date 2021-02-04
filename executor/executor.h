#ifndef EXECUTER_H
# define EXECUTER_H

# include <dirent.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "minishell.h"

# define WRONG_COMMAND 1
# define MANY_ARGS 2
# define MALLOC_ERROR 3
# define FD_ERROR 4

typedef struct tools
{
	char **path;
	int tmp_fd[2];
	int exit_code;
}				s_tools;


int				g_last_res;

void			handle_error(int code, const char *command);
void			handle_cd_error(char *path);
void			executor(t_cmd *cmd, char ***envp, s_tools *tools);
int				free_dpointer_no_size(void **p);
void			signal_handler(int sig);
void			input_signal_handler(int sig);
void			show_promt();
int				minishell_exit();
#endif
