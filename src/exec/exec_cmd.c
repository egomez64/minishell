/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:40:39 by maamine           #+#    #+#             */
/*   Updated: 2024/06/17 15:14:05 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	child(t_exec *exec, t_env *env, char **envp, t_exec **lst)
{
	int				err;
	t_attributes	attributes;

	close_and_set(&exec->next->in_fd);
	attributes = fill_attributes(exec, env, envp);
	if (!attributes.pathname)
		return (1);
	err = make_redirections(exec);
	if (err)
	{
		free_attributes(attributes);	// 
		return (err);
	}
	execve(attributes.pathname, attributes.argv, attributes.envp);
	err = errno;
	perror("minishell ");
	free_attributes(attributes);	// 
	clear_exec(lst);
	return (err);
}

static void	parent(t_exec *exec)
{
	close_and_set(&exec->in_fd);
	close_and_set(&exec->out_fd);
}

void	exec_cmd(t_exec *exec, t_env *env, char **envp, t_exec **lst)
{
	int	err;

	exec->cpid = fork();
	if (exec->cpid == -1)
		perror("fork");
	if (exec->cpid == 0)
	{
		err = child(exec, env, envp, lst);
		exit(err);
	}
	parent(exec);
}
