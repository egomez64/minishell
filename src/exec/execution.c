/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:50:53 by maamine           #+#    #+#             */
/*   Updated: 2024/07/29 14:14:44 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_sig;

static int	wait_last_pid(int wstatus)
{
	if (!WIFSIGNALED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WTERMSIG(wstatus) == SIGQUIT)
		write(2, "Quit\n", 6);
	return (128 + WTERMSIG(wstatus));
}

/// @brief Waits for every command to end.
/// @return Exit status of the last command.
static int	wait_for_everyone(t_cmd **cmd)
{
	int		exit_status;
	int		wstatus;
	pid_t	pid;
	pid_t	last_pid;
	int		sig;

	exit_status = -1;
	pid = 0;
	last_pid = cmd_last(*cmd)->pid;
	sig = 0;
	while (pid != -1)
	{
		pid = wait(&wstatus);
		if (!sig && WIFSIGNALED(wstatus))
			sig = WTERMSIG(wstatus);
		if (pid == last_pid)
			exit_status = wait_last_pid(wstatus);
	}
	if (sig == SIGINT)
		write(2, "\n", 2);
	return (exit_status);
}

// /// @brief Waits for every command to end.
// /// @return Exit status of the last command.
// static int	wait_for_everyone(t_cmd **cmd)
// {
// 	int		exit_status;
// 	int		wstatus;
// 	pid_t	pid;
// 	pid_t	last_pid;
// 	int		sig_handler;
//
// 	exit_status = -1;
// 	pid = 0;
// 	last_pid = cmd_last(*cmd)->pid;
// 	sig_handler = 0;
// 	while (pid != -1)
// 	{
// 		pid = wait(&wstatus);
// 		if (pid == last_pid && WIFEXITED(wstatus))
// 			exit_status = WEXITSTATUS(wstatus);
// 		else if (WIFSIGNALED(wstatus) && !sig_handler)
// 		{
// 			if (pid == last_pid)
// 				exit_status = sig_exec(wstatus/*, true*/);
// 			else
// 				sig_exec(wstatus/*, false*/);
// 			sig_handler = 1;
// 		}
// 	}
// 	return (exit_status);
// }

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
		exit_status = handle_builtin(minish->commands, minish, stdfd);
	else
	{
		fork_cmd(minish->commands, minish, stdfd);
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
		fork_cmd(current, minish, stdfd);
		current = current->next;
	}
	fork_cmd(current, minish, stdfd);
	exit_status = wait_for_everyone(&minish->commands);
	restore_stdfd(stdfd);
	return (exit_status);
}

// static void	set_input_output(t_cmd *cmd)
// {
// 	if (cmd->input_fd == -1)
// 		cmd->input_fd = 0;
// 	while (cmd->next)
// 		cmd = cmd->next;
// 	if (cmd->output_fd == -1)
// 		cmd->output_fd = 1;
// }

int	execution(t_minishell *minish)
{
	int		exit_status;
	t_cmd	*cmd;

	if (minish->commands == NULL)
		return (0);
	cmd = minish->commands;
	if (cmd->input_fd == -1)
		cmd->input_fd = 0;
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->output_fd == -1)
		cmd->output_fd = 1;
	if (!minish->commands->next)
		exit_status = simple_exec(minish);
	else
		exit_status = pipes_exec(minish);
	// if (exit_status == -1)
	// {
	// 	
	// }
	return (exit_status);
}

// int	execution(t_minishell *minish)
// {
// 	int		exit_status;
// 
// 	if (minish->commands == NULL)
// 		return (0);
// 	// set_input_output(minish->commands);
// 	if (!minish->commands->next)
// 		exit_status = simple_exec(minish);
// 	else
// 		exit_status = pipes_exec(minish);
// 	// if (exit_status == -1)
// 	// {
// 	// 	
// 	// }
// 	return (exit_status);
// }
