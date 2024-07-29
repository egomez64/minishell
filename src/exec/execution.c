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

static int	wait_for_everyone(t_cmd **cmd)
{
	int			exit_status;
	int			wstatus;
	pid_t		pid;
	const pid_t	last_pid = cmd_last(*cmd)->pid;
	int			sig;

	exit_status = -1;
	pid = 0;
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

int	execution(t_minishell *minish)
{
	int	exit_status;
	int	*output_fd;

	if (minish->commands == NULL)
		return (0);
	if (minish->commands->input_fd == -1)
		minish->commands->input_fd = 0;
	output_fd = &cmd_last(minish->commands)->output_fd;
	if (*output_fd == -1)
		*output_fd = 1;
	if (!minish->commands->next)
		exit_status = simple_exec(minish);
	else
		exit_status = pipes_exec(minish);
	return (exit_status);
}
