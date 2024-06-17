/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:40:39 by maamine           #+#    #+#             */
/*   Updated: 2024/06/17 18:55:26 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	child(t_exec *exec, t_env *env, char **envp, t_exec **lst)
{
	int				err;
	t_attributes	attributes;

	if (exec->next)
	{
		dprintf(3, "%d: close_and_set %d\n", getpid(), exec->next->in_fd);
		close_and_set(&exec->next->in_fd);
	}
	attributes = fill_attributes(exec, env, envp);
	dprintf(3, "%d: pathname: %s\n", getpid(), attributes.pathname);
	if (!attributes.pathname)
		return (1);
	// dprintf(3, "%d: make_redirs...\n", getpid());
	// err = make_redirections(exec);
	// dprintf(3, "%d: redirs done.\n", getpid());
	// if (err)
	// {
	// 	free_attributes(attributes);	// 
	// 	return (err);
	// }
	dprintf(3, "%d: execve\n", getpid());
	execve(attributes.pathname, attributes.argv, attributes.envp);
	err = errno;
	perror("minishell ");
	free_attributes(attributes);	// 
	clear_exec(lst);
	return (err);
}

static void	parent(t_exec *exec)
{
	dprintf(3, "close_and_set %d and %d\n", exec->in_fd, exec->out_fd);
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
