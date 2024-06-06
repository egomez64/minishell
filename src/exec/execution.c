/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:50:53 by maamine           #+#    #+#             */
/*   Updated: 2024/06/06 17:10:27 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clear_exec(t_exec **lst)
{
	t_exec	*current;
	t_exec	*next;

	current = *lst;
	cmd_clear(current->cmd);	// 
	while (current)
	{
		next = current->next;
		close_and_set(current->in_fd);
		close_and_set(current->out_fd);
		current = next;
	}
	*lst = NULL;
}

static t_exec	*exec_new(t_cmd *cmd)
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

static t_exec	*cmd_to_exec(t_cmd *cmd)
{
	t_exec	*lst;
	t_exec	*exec;

	if (!cmd)
		return (NULL);
	exec = exec_new(cmd);
	if (!exec)
		return (NULL);
	lst = exec;
	while (cmd->next)
	{
		exec->next = exec_new(cmd->next);
		if (!exec->next)
		{
			perror("malloc");
			clear_exec(&lst);
			return (NULL);
		}
		exec = exec->next;
		cmd = cmd->next;
	}
	return (lst);
}

int execution(t_cmd *cmd, t_env	*env)
{
	t_exec	*exec;
	char	**envp;
	int		exit_status;

	if (!cmd)
		return (0);
	exec = cmd_to_exec(cmd);
	if (!exec)
		return (1);
	envp = envlst_to_envp(env);
	if (!envp)
	{
		clear_exec(&exec);
		return (1);
	}
	while (exec->next)
	{
		open_pipe(exec);
		exec_cmd(exec, env, envp);
		exec = exec->next;
	}
	exec_cmd(exec, env, envp);
	exit_status = wait_for_everyone(exec);
	return (exit_status);
}
