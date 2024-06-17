/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:25:14 by maamine           #+#    #+#             */
/*   Updated: 2024/06/17 15:10:26 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec	*exec_new(t_cmd *cmd)
{
	t_exec	*exec;

	exec = malloc(sizeof (t_exec));
	if (!exec)
		return (NULL);
	exec->cmd = cmd;
	exec->in_fd = -1;
	exec->out_fd = -1;
	exec->cpid = -1;
	exec->next = NULL;
	return (exec);
}

t_exec	*exec_lstlast(t_exec *exec)
{
	if (!exec)
		return (NULL);
	while (exec->next)
		exec = exec->next;
	return (exec);
}

void	clear_exec(t_exec **lst)
{
	t_exec	*current;

	current = *lst;
	while (current)
	{
		cmd_clear(current->cmd);	// 
		close_and_set(&current->in_fd);
		close_and_set(&current->out_fd);
		current = current->next;
	}
	*lst = NULL;
}
