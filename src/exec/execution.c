/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:50:53 by maamine           #+#    #+#             */
/*   Updated: 2024/06/26 18:49:08 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static t_exec	*cmd_to_exec(t_cmd *cmd)
// {
// 	t_exec	*lst;
// 	t_exec	*exec;
// 
// 	if (!cmd)
// 		return (NULL);
// 	exec = exec_new(cmd);
// 	if (!exec)
// 		return (NULL);
// 	lst = exec;
// 	while (cmd->next)
// 	{
// 		exec->next = exec_new(cmd->next);
// 		if (!exec->next)
// 		{
// 			perror("malloc");
// 			clear_exec(&lst);
// 			return (NULL);
// 		}
// 		exec = exec->next;
// 		cmd = cmd->next;
// 	}
// 	return (lst);
// }

// /// @brief Waits for every command to end.
// /// @return Exit status of the last command.
// static int	wait_for_everyone(t_exec **exec)
// {
// 	int		exit_status;
// 	int		wstatus;
// 	pid_t	last_pid;
// 	pid_t	pid;
// 
// 	pid = 0;
// 	wstatus = 0;
// 	exit_status = 0;
// 	last_pid = exec_lstlast(*exec)->cpid;
// 	while (pid != -1)
// 	{
// 		dprintf(3, "waiting...\n");
// 		pid = wait(&wstatus);
// 		dprintf(3, "wait %d\n", pid);
// 		if (pid == last_pid)
// 		{
// 			exit_status = WEXITSTATUS(wstatus);
// 			dprintf(3, "exit_status: %d\n", exit_status);
// 		}
// 	}
// 	// dprintf(3, "clear_exec\n");
// 	// clear_exec(exec);
// 	return (exit_status);
// }

// static t_cmd	*cmd_last(t_cmd *cmd)
// {
// 	if (!cmd)
// 		return (NULL);
// 	while (cmd->next)
// 		cmd = cmd->next;
// 	return (cmd);
// }

/// @brief Waits for every command to end.
/// @return Exit status of the last command.
static int	wait_for_everyone(t_cmd **cmd)
{
	int		exit_status;
	int		wstatus;
	pid_t	last_pid;
	pid_t	pid;

	pid = 0;
	wstatus = 0;
	exit_status = 0;
	last_pid = cmd_last(*cmd)->pid;
	while (pid != -1)
	{
		dprintf(3, "waiting...\n");
		pid = wait(&wstatus);
		dprintf(3, "wait %d\n", pid);
		if (pid == last_pid)
		{
			exit_status = WEXITSTATUS(wstatus);
			dprintf(3, "exit_status: %d\n", exit_status);
		}
	}
	return (exit_status);
}

// static int	simple_exec(t_exec **exec, t_env **env)
// {
// 	int	exit_status;
// 	int	stdfd[2];
// 
// 	dprintf(3, "simple_exec\n");
// 	if ((*exec)->cmd->arguments
// 		&& is_builtins((char *)((*exec)->cmd->arguments->content)))
// 	{
// 		dprintf(3, "builtin\n");
// 		exit_status = handle_builtins((*exec)->cmd, env);
// 	}
// 	else
// 	{
// 		dup_stdfd(stdfd);
// 		dprintf(3, "exec_cmd\n");
// 		exec_cmd(*exec, env, exec);
// 		exit_status = wait_for_everyone(exec);
// 		restore_stdfd(stdfd);
// 	}
// 	return (exit_status);
// }

static int	simple_exec(t_minishell *minish)
{
	int	exit_status;
	int	stdfd[2];

	dprintf(3, "simple_exec\n");
	if (minish->commands->arguments
		&& is_builtins((char *)(minish->commands->arguments->content)))
	{
		dprintf(3, "builtin\n");
		exit_status = handle_builtins(minish);
	}
	else
	{
		dup_stdfd(stdfd);
		dprintf(3, "exec_cmd\n");
		exec_cmd(minish->commands, &minish->envi, &minish->commands);
		exit_status = wait_for_everyone(&minish->commands);
		restore_stdfd(stdfd);
	}
	return (exit_status);
}

// static int	pipes_exec(t_exec **exec, t_env **env)
// {
// 	int		exit_status;
// 	t_exec	*current;
// 	int		stdfd[2];
// 
// 	dprintf(3, "pipes_exec\n");
// 	dup_stdfd(stdfd);
// 	current = *exec;
// 	while (current->next)
// 	{
// 		open_pipe(current);
// 		exec_cmd(current, env, exec);
// 		current = current->next;
// 	}
// 	exec_cmd(current, env, exec);
// 	exit_status = wait_for_everyone(exec);
// 	restore_stdfd(stdfd);
// 	return (exit_status);
// }

static int	pipes_exec(t_cmd **cmds, t_env **env)
{
	int		exit_status;
	t_cmd	*current;
	int		stdfd[2];

	dprintf(3, "pipes_exec\n");
	dup_stdfd(stdfd);
	current = *cmds;
	while (current->next)
	{
		open_pipe(current);
		exec_cmd(current, env, cmds);
		current = current->next;
	}
	exec_cmd(current, env, cmds);
	exit_status = wait_for_everyone(cmds);
	restore_stdfd(stdfd);
	return (exit_status);
}

static void	print_cmd(t_cmd *cmd)	// 
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
		dprintf(3, "input_fd: %d, output_fd: %d, exit_status: %d\n", cmd->input_fd, cmd->output_fd, cmd->exit_s);
		cmd = cmd->next;
	}
	dprintf(3, "\n");
}

// static void	print_env(t_env *env)
// {
// 	dprintf(3, "env:\n");
// 	while (env)
// 	{
// 		dprintf(3, "\t%s=%s\n", env->name, env->val);
// 		env = env->next;
// 	}
// }

// static void	set_input_output(t_exec *exec)
// {
// 	if (exec->cmd->input_fd == -1)
// 		exec->cmd->input_fd = 0;
// 	while (exec->next)
// 		exec = exec->next;
// 	if (exec->cmd->output_fd == -1)
// 		exec->cmd->output_fd = 1;
// }

static void	set_input_output(t_cmd *cmd)
{
	if (cmd->input_fd == -1)
		cmd->input_fd = 0;
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->output_fd == -1)
		cmd->output_fd = 1;
}

int	execution(t_minishell *minishell)
{
	// t_exec	*exec;
	// // char	**envp;
	int		exit_status;

	if (minishell->commands == NULL)
		return (0);
	// // print_env(env);	// 
	// exec = cmd_to_exec(minishell->commands);
	// if (!exec)
	// 	return (1);
	// set_input_output(exec);
	set_input_output(minishell->commands);
	print_cmd(minishell->commands);	//
	// // envp = envlst_to_envp(env);
	// // if (!envp)
	// // {
	// // 	clear_exec(&exec);
	// // 	return (1);
	// // }
	// if (!exec->next)
	// 	exit_status = simple_exec(&exec, &minishell->envi);
	// else
	// 	exit_status = pipes_exec(&exec, &minishell->envi);
	if (!minishell->commands->next)
		exit_status = simple_exec(minishell);
	else
		exit_status = pipes_exec(&minishell->commands, &minishell->envi);
	return (exit_status);
}
