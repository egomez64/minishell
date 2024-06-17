/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:50:53 by maamine           #+#    #+#             */
/*   Updated: 2024/06/17 15:31:13 by maamine          ###   ########.fr       */
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
	dprintf(3, "exec_lstlast\n");
	last_pid = exec_lstlast(*exec)->cpid;
	while (pid != -1)
	{
		dprintf(3, "wait ");
		pid = wait(&wstatus);
		dprintf(3, "%d", pid);
		if (pid == last_pid)
		{
			exit_status = WEXITSTATUS(wstatus);
			dprintf(3, ", exit_status: %d", exit_status);
		}
		dprintf(3, "\n");
	}
	// dprintf(3, "clear_exec\n");
	// clear_exec(exec);
	return (exit_status);
}

static void	print_cmd(t_cmd *cmd)
{
	t_list	*arg;
	t_token	*redir;

	while (cmd)
	{
		dprintf(3, "arg\n");
		arg = cmd->arguments;
		while (arg)
		{
			dprintf(3, "\t%s\n", (char *) arg->content);
			arg = arg->next;
		}
		dprintf(3, "redir\n");
		redir = cmd->redirections;
		while (redir)
		{
			dprintf(3, "\t%s\n", redir->val);
			redir = redir->next;
		}
		dprintf(3, ".\n");
		cmd = cmd->next;
	}
}

int execution(t_cmd *cmd, t_env	*env)
{
	t_exec	*exec;
	t_exec	*current;
	char	**envp;
	int		exit_status;

	if (!cmd)
		return (0);
	dprintf(3, "cmd_lst:\n");
	print_cmd(cmd);
	dprintf(3, "cmd_to_exec\n");
	exec = cmd_to_exec(cmd);
	if (!exec)
		return (1);
	dprintf(3, "envlst_to_envp\n");
	envp = envlst_to_envp(env);
	if (!envp)
	{
		clear_exec(&exec);
		return (1);
	}
	current = exec;
	dprintf(3, "while (current->next) {\n");
	while (current->next)
	{
		dprintf(3, "open_pipe\n");
		open_pipe(current);
		dprintf(3, "exec_cmd\n");
		exec_cmd(current, env, envp, &exec);
		current = current->next;
	}
	dprintf(3, "}\nexec_cmd\n");
	exec_cmd(current, env, envp, &exec);
	dprintf(3, "wait_for_everyone\n");
	exit_status = wait_for_everyone(&exec);
	return (exit_status);
}
