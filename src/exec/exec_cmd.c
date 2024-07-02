/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:40:39 by maamine           #+#    #+#             */
/*   Updated: 2024/07/02 15:22:16 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	child(t_cmd *cmd, t_env **env, t_cmd **lst)
// {
// 	int				err;
// 	t_attributes	attributes;
// 
// 	if (cmd->next)
// 	{
// 		// dprintf(3, "%d: close_and_set %d\n", getpid(), cmd->next->input_fd);
// 		close_and_set(&cmd->next->input_fd);
// 	}
// 	make_redirections(cmd);
// 	attributes = fill_attributes(cmd->arguments, env);
// 	if (!attributes.pathname)
// 		return (1);
// 	// dprintf(3, "%d: execve\n", getpid());
// 	execve(attributes.pathname, attributes.argv, attributes.envp);
// 	err = errno;
// 	perror("minishell ");
// 	free_attributes(attributes);	// 
// 	(void) lst;						// 
// 	// clear_exec(lst);				// 
// 	return (err);
// }

// static void	parent(t_cmd *cmd)
// {
// 	// dprintf(3, "close_and_set %d and %d\n", cmd->input_fd, cmd->output_fd);
// 	close_and_set(&cmd->input_fd);
// 	close_and_set(&cmd->output_fd);
// }

// void	exec_cmd(t_cmd *cmd, t_env **env, t_cmd **cmd_lst)
// {
// 	int	err;
// 
// 	cmd->pid = fork();
// 	if (cmd->pid == -1)
// 		perror("fork");
// 	if (cmd->pid == 0)
// 	{
// 		err = child(cmd, env, cmd_lst);
// 		exit(err);
// 	}
// 	parent(cmd);
// }

int	exec_cmd(t_cmd *cmd, t_minishell *minish)
{
	int				err;
	t_attributes	attributes;

	attributes = fill_attributes(cmd->arguments, &minish->envi);
	if (!attributes.pathname)
		return (1);				// 
	if (*attributes.pathname == '\0')
		return (127);				// 
	// dprintf(3, "%d: execve\n", getpid());
	execve(attributes.pathname, attributes.argv, attributes.envp);
	err = errno;
	perror("minishell ");
	// free_attributes(attributes);	// 
	// (void) lst;						// `lst` becomes `&minish->commands`
	// // clear_exec(lst);				// 
	return (err);
}

int	child(t_cmd *cmd, t_minishell *minish)
{
	if (cmd->next)
	{
		// dprintf(3, "%d: close_and_set %d\n", getpid(), cmd->next->input_fd);
		close_and_set(&cmd->next->input_fd);
	}
	make_redirections(cmd);
	if (is_builtin(cmd->arguments->content))
		return (handle_builtin(cmd, minish));
	else
		return (exec_cmd(cmd, minish));
}

void	fork_cmd(t_cmd *cmd, t_minishell *minish)
{
	int	err;

	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("fork");
	if (cmd->pid == 0)
	{
		signal(SIGINT, SIG_DFL);		// 
		signal(SIGQUIT, SIG_DFL);		// 
		err = child(cmd, minish);
		exit(err);
	}
	// dprintf(3, "close_and_set %d and %d\n", cmd->input_fd, cmd->output_fd);
	close_and_set(&cmd->input_fd);
	close_and_set(&cmd->output_fd);
}
