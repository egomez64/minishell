/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:40:39 by maamine           #+#    #+#             */
/*   Updated: 2024/06/26 18:21:58 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	print_cmd(t_cmd *cmd)	// 
// {
// 	t_list	*arg;
// 	t_token	*redir;
// 
// 	while (cmd)
// 	{
// 		dprintf(3, "%d: arg\n", getpid());
// 		arg = cmd->arguments;
// 		while (arg)
// 		{
// 			dprintf(3, "%d: \t%s\n", getpid(), (char *) arg->content);
// 			arg = arg->next;
// 		}
// 		dprintf(3, "%d: redir\n", getpid());
// 		redir = cmd->redirections;
// 		while (redir)
// 		{
// 			dprintf(3, "%d: \t%s\n", getpid(), redir->val);
// 			redir = redir->next;
// 		}
// 		dprintf(3, "%d: input_fd: %d, output_fd: %d, exit_status: %d\n", getpid(), cmd->input_fd, cmd->output_fd, cmd->exit_s);
// 		cmd = cmd->next;
// 	}
// 	dprintf(3, "%d: \n", getpid());
// }

// static void	print_exec(t_exec *exec, t_attributes *att)	// 
// {
// 	char	**argv;
// 
// 	dprintf(3, "%d: print_cmd\n", getpid());
// 	print_cmd(exec->cmd);
// 	dprintf(3, "%d: pathname: %s\n", getpid(), att->pathname);
// 	argv = att->argv;
// 	dprintf(3, "%d: argv:\n", getpid());
// 	while (*argv)
// 	{
// 		dprintf(3, "%d: \t%s\n", getpid(), *argv);
// 		argv++;
// 	}
// }

// static int	child(t_exec *exec, t_env **env, t_exec **lst)
// {
// 	int				err;
// 	t_attributes	attributes;
// 
// 	if (exec->next)
// 	{
// 		dprintf(3, "%d: close_and_set %d\n", getpid(), exec->next->cmd->input_fd);
// 		close_and_set(&exec->next->cmd->input_fd);
// 	}
// 	make_redirections(exec);
// 	attributes = fill_attributes(exec, env/*, envp*/);
// 	if (!attributes.pathname)
// 		return (1);
// 	// print_exec(exec, &attributes);	// 
// 	dprintf(3, "%d: execve\n", getpid());
// 	execve(attributes.pathname, attributes.argv, attributes.envp);
// 	err = errno;
// 	perror("minishell ");
// 	free_attributes(attributes);	// 
// 	clear_exec(lst);
// 	return (err);
// }

static int	child(t_cmd *cmd, t_env **env, t_cmd **lst)
{
	int				err;
	t_attributes	attributes;

	if (cmd->next)
	{
		dprintf(3, "%d: close_and_set %d\n", getpid(), cmd->next->input_fd);
		close_and_set(&cmd->next->input_fd);
	}
	make_redirections(cmd);
	attributes = fill_attributes(cmd->arguments, env);
	if (!attributes.pathname)
		return (1);
	dprintf(3, "%d: execve\n", getpid());
	execve(attributes.pathname, attributes.argv, attributes.envp);
	err = errno;
	perror("minishell ");
	free_attributes(attributes);	// 
	(void) lst;						// 
	// clear_exec(lst);				// 
	return (err);
}

// static void	parent(t_exec *exec)
// {
// 	dprintf(3, "close_and_set %d and %d\n", exec->cmd->input_fd, exec->cmd->output_fd);
// 	// if (exec->cmd->input_fd != 0)
// 	close_and_set(&exec->cmd->input_fd);
// 	// if (exec->cmd->output_fd != 1)
// 	close_and_set(&exec->cmd->output_fd);
// }

static void	parent(t_cmd *cmd)
{
	dprintf(3, "close_and_set %d and %d\n", cmd->input_fd, cmd->output_fd);
	close_and_set(&cmd->input_fd);
	close_and_set(&cmd->output_fd);
}

// void	exec_cmd(t_exec *exec, t_env **env, t_exec **lst)
// {
// 	int	err;
// 
// 	exec->cpid = fork();
// 	if (exec->cpid == -1)
// 		perror("fork");
// 	if (exec->cpid == 0)
// 	{
// 		err = child(exec, env, lst);
// 		exit(err);
// 	}
// 	parent(exec);
// }

void	exec_cmd(t_cmd *cmd, t_env **env, t_cmd **cmd_lst)
{
	int	err;

	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("fork");
	if (cmd->pid == 0)
	{
		err = child(cmd, env, cmd_lst);
		exit(err);
	}
	parent(cmd);
}
