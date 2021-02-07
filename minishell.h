/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoaney <fmoaney@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:02:00 by fmoaney           #+#    #+#             */
/*   Updated: 2021/02/07 12:35:10 by fmoaney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# ifndef G_PRESTR
#  define G_PRESTR "minishell->"
# endif

# define WRONG_COMMAND 1
# define MANY_ARGS 2
# define MALLOC_ERROR 3
# define FD_ERROR 4

# define SPEC_CHARS "\n><|;"
# define REPLACE_M "\a"

typedef struct	s_cmd
{
	char		*command;
	char		**args;
	int			fl_pipe;
	int			fl_append;
	char		*file_in;
	char		*file_out;
	int			fd[2];
}				t_cmd;

/*
** MAIN built-in functions:
*/

int				ft_env(char **env);
int				ft_pwd(void);
int				ft_cd(char *path);
int				ft_echo(char **args);
int				ft_export(char **vars, char ***env);
int				ft_unset(char **names, char ***env);
int				ft_exit(char **args);

/*
** ------------------------
*/

void			print_cmd(t_cmd *cmd);

int				handle_error(int code, const char *command);
void			*ft_realloc(void *buf, size_t old_size, size_t new_size);
void			*safe_realloc(void *buf, size_t index, size_t membsz);
void			*normalize_arr(void *arr, size_t size, size_t membsz);
t_cmd			*newcmd(void);
void			delcmd(void *command);
int				is_curdir(char *p);
int				is_pardir(char *p);
int				is_path(char *p);
char			*join_path(char *p1, char *p2, size_t p2_end);
char			*get_cur_path(void);
char			*get_env_var(char *name, char **env);
char			*get_abs_path(char *dir, char *file_name);
char			*get_abs_parent(char *dir);
char			*get_abs_path_command(char *cmd, char **env);
int				set_last_red_file(t_cmd **cmd);
int				is_eof(void);
int				get_size(char **buf);
int				get_old_size(int i);
int				is_correct_name(char *name, size_t len);
int				decrease_shlvl(char *shlvl_val, char ***env);
int				increase_shlvl(char *shlvl_val, char ***env);
int				merge_dpointer(void ***dst, void **p);
char			*ft_strreplace(char *dst, const char *old, const char *new);
int				prepare_cmd(t_cmd *cmd, char **env);
int				replace_dollar_question(t_cmd *cmd, int val);
int				ft_getch(void);
void			ft_ungetch(void);
int				skip_spaces(void);
int				free_dpointer(void ***p, size_t nmemb);
char			**parse_path(char **envp);
int				parse_escaped_seq(char **buf, int index, int esc_all);
int				parse_dollar_seq(char **buf, int index, char **env);
char			*parse_seq(char **env);
int				parse_squote(char **buf, int i);
int				parse_dquote(char **buf, int i, char **env);
char			*parse_dollar(char **env);
t_cmd			**parse_cmd_line(char **env);
void			free_cmd(t_cmd **cmd);
#endif
