/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:40:39 by maamine           #+#    #+#             */
/*   Updated: 2024/06/06 15:35:46 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	child(t_exec *exec, char **envp, t_exec **lst)
{
	int				err;
	t_attributes	attributes;

	attributes = fill_attributes(exec, envp);
	if (err)
		return (err);
	err = make_redirections(exec);
	if (err)
	{
		free_attributes(attributes);
		return (err);
	}
	execve(attributes.pathname, attributes.argv, attributes.envp);
	err = errno;
	perror("minishell ");
	free_attributes(attributes);
	close_exec(lst);
	return (err);
}

void	exec_cmd(t_exec *exec, char **envp, t_exec **lst)
{
	int	err;

	exec->cpid = fork();
	if (exec->cpid == -1)
		perror("fork");
	if (exec->cpid == 0)
	{
		err = child(exec, envp, lst);
		exit(err);
	}
	parent(exec);
}
