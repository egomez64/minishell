/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:07:57 by maamine           #+#    #+#             */
/*   Updated: 2024/06/25 19:22:29 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <parsing.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_string
{
	char	*ptr;
	int		size;
}			t_string;

typedef struct s_exec
{
	t_cmd			*cmd;
	__pid_t			cpid;
	struct s_exec	*next;
}					t_exec;

typedef struct s_attributes
{
	char	*pathname;
	char	**argv;
	char	**envp;
}			t_attributes;

t_exec	*exec_new(t_cmd *cmd);
t_exec	*exec_lstlast(t_exec *exec);
void	clear_exec(t_exec **lst);

int		execution(t_cmd *cmd, t_env *env);
int		open_pipe(t_exec *exec);
int		make_redirections(t_exec *exec);
void	exec_cmd(t_exec *exec, t_env *env, t_exec **lst);

int		dup_stdfd(int stdfd[2]);
int		restore_stdfd(int stdfd[2]);

t_attributes
		fill_attributes(t_exec *exec, t_env *env);
void	free_attributes(t_attributes attributes);
char	*find_pathname(char *exec_name, char *envp_path);
char	**envlst_to_envp(t_env *env);

void	close_and_set(int *fd);

#endif
