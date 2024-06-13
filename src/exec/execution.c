/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:50:53 by maamine           #+#    #+#             */
/*   Updated: 2024/06/10 11:31:50 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/// @brief Waits for every command to end.
/// @return Exit status of the last command.
static int	wait_for_everyone(t_exec **exec)
{
	int		exit_status;
	int		wstatus;
	pid_t	last_pid;
	pid_t	pid;

	pid = 0;
	wstatus = 0;
	exit_status = 0;
	last_pid = exec_lstlast(*exec)->cpid;
	while (pid != -1)
	{
		pid = wait(&wstatus);
		if (pid == last_pid)
			exit_status = WEXITSTATUS(wstatus);
	}
	clear_exec(exec);
	return (exit_status);
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
