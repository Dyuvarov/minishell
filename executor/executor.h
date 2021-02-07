/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:31:37 by ugreyiro          #+#    #+#             */
/*   Updated: 2021/02/07 15:25:12 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <dirent.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "minishell.h"

typedef struct	s_tools
{
	int			tmp_fd[2];
	int			exit_code;
}				t_tools;

int				g_last_res;

int				free_dpointer_no_size(void **p);
int				execute_cd(char *new_path, char **env);
void			execute_in_current_process(t_cmd *cmd, char ***env, t_tools *tools);
void			handle_cd_error(char *path);
void			executor(t_cmd *cmd, char ***envp, t_tools *tools);
void			handle_cd_error(char *path);
void			executor(t_cmd *cmd, char ***envp, t_tools *tools);
void			signal_handler(int sig);
void			input_signal_handler(int sig);
void			show_promt();
int				minishell_exit();
#endif
