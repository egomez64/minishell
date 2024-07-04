/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:50:53 by maamine           #+#    #+#             */
/*   Updated: 2024/07/03 18:35:05 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_sig;

/// @brief Waits for every command to end.
/// @return Exit status of the last command.
static int	wait_for_everyone(t_cmd **cmd)
{
	int		exit_status;
	int		wstatus;
	pid_t	last_pid;
	pid_t	pid;
	int		sig_handler;

	pid = 0;
	wstatus = 0;
	exit_status = 0;
	last_pid = cmd_last(*cmd)->pid;
	sig_handler = 0;
	while (pid != -1)
	{
		pid = wait(&wstatus);
		if (pid == last_pid && WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus) && !sig_handler)
		{
			if (pid == last_pid)
		 		exit_status = sig_exec(wstatus);
		 	else
				sig_exec(wstatus);
			sig_handler = 1;
		}
	}
	// if (WIFEXITED(wstatus))
	// 	sig_exec(wstatus);
	return (exit_status);
}

static int	simple_exec(t_minishell *minish)
{
	int	exit_status;
	int	stdfd[2];

	if (minish->commands->exit_s)
		return (minish->commands->exit_s);
	dup_stdfd(stdfd);
	make_redirections(minish->commands);
	if (minish->commands->arguments
		&& is_builtin((char *)(minish->commands->arguments->content)))
		exit_status = handle_builtin(minish->commands, minish);
	else
	{
		fork_cmd(minish->commands, minish);
		exit_status = wait_for_everyone(&minish->commands);
	}
	restore_stdfd(stdfd);
	return (exit_status);
}

static int	pipes_exec(t_minishell *minish)
{
	int		exit_status;
	t_cmd	*current;
	int		stdfd[2];

	dup_stdfd(stdfd);
	current = minish->commands;
	while (current->next)
	{
		open_pipe(current);
		fork_cmd(current, minish);
		current = current->next;
	}
	fork_cmd(current, minish);
	exit_status = wait_for_everyone(&minish->commands);
	restore_stdfd(stdfd);
	return (exit_status);
}

// static void	print_cmd(t_cmd *cmd)	// 
// {
// 	t_list	*arg;
// 	t_token	*redir;
// 
// 	while (cmd)
// 	{
// 		// dprintf(3, "arg\n");
// 		arg = cmd->arguments;
// 		while (arg)
// 		{
// 			// dprintf(3, "\t%s\n", (char *) arg->content);
// 			arg = arg->next;
// 		}
// 		// dprintf(3, "redir\n");
// 		redir = cmd->redirections;
// 		while (redir)
// 		{
// 			// dprintf(3, "\t%s\n", redir->val);
// 			redir = redir->next;
// 		}
// 		// dprintf(3, "input_fd: %d, output_fd: %d, exit_status: %d\n", cmd->input_fd, cmd->output_fd, cmd->exit_s);
// 		cmd = cmd->next;
// 	}
// 	// dprintf(3, "\n");
// }

static void	set_input_output(t_cmd *cmd)
{
	// if (cmd->input_fd == -2)
	if (cmd->input_fd == -1)
		cmd->input_fd = 0;
	while (cmd->next)
		cmd = cmd->next;
	// if (cmd->output_fd == -2)
	if (cmd->output_fd == -1)
		cmd->output_fd = 1;
}

int	execution(t_minishell *minish)
{
	int		exit_status;

	if (minish->commands == NULL)
		return (0);
	set_input_output(minish->commands);
	if (!minish->commands->next)
		exit_status = simple_exec(minish);
	else
		exit_status = pipes_exec(minish);
	return (exit_status);
}
