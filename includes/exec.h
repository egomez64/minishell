/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:07:57 by maamine           #+#    #+#             */
/*   Updated: 2024/07/20 15:33:26 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <parsing.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_string
{
	char	*ptr;
	int		size;
}			t_string;

typedef struct s_attributes
{
	char	*pathname;
	char	**argv;
	char	**envp;
}			t_attributes;

int				execution(t_minishell *minishell);

int				open_pipe(t_cmd *cmd);
int				make_redirections(t_cmd *cmd);
int				exec_cmd(t_cmd *cmd, t_minishell *minish);
void			fork_cmd(t_cmd *cmd, t_minishell *minish, int stdfd[2]);

int				dup_stdfd(int stdfd[2]);
int				restore_stdfd(int stdfd[2]);

t_attributes	fill_attributes(t_list *args, t_env **env);
void			free_attributes(t_attributes attributes);
char			*find_pathname(char *exec_name, char *envp_path);
char			**envlst_to_envp(t_env **env);

void			close_and_set(int *fd);

void			normal_c(int signal);
void			heredoc_c(int signal);
int				sig_exec(int wstatus);

void			str_error_message(char *name, char *err);
int				is_dir(char *str);
int				locate_and_replace(char *name, char *envp_path);
int				check_name(char *str, char *envp_path);

#endif
