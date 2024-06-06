/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:07:57 by maamine           #+#    #+#             */
/*   Updated: 2024/06/06 16:17:20 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include <unistd.h>
#include <parsing.h>
#include <errno.h>

typedef struct s_string
{
	char	*ptr;
	int		size;
}			t_string;

typedef struct s_exec t_exec;
typedef struct s_exec
{
	t_cmd	*cmd;
	int		in_fd;
	int		out_fd;
	__pid_t	cpid;
	t_exec	*next;
}			t_exec;

typedef struct s_attributes
{
	char	*pathname;
	char	**argv;
	char	**envp;
}			t_attributes;


int 			execution(t_cmd *cmd, t_env *env);
int				open_pipe(t_exec *exec);
t_attributes	fill_attributes(t_exec *exec, char **envp);
char			*find_pathname(char *exec_name, char *envp_path);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                  :::      ::::::::         */
/*                                                 :+:      :+:    :+:        */
/*                                                +:+ +:+         +:+         */
/*                                               +#+  +:+       +#+           */
/*                                              +#+#+#+#+#+   +#+             */
/*                                                    #+#    #+#              */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */