/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:40:39 by maamine           #+#    #+#             */
/*   Updated: 2024/07/18 16:13:05 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_cmd(t_cmd *cmd, t_minishell *minish)
{
	int				err;
	t_attributes	attributes;

// 	if (check_name(cmd->arguments->content, &err))
// 		return (err);
	attributes = fill_attributes(cmd->arguments, &minish->envi);
	if (!attributes.pathname)
		return (1);				// 
	if (*attributes.pathname == '\0')
		return (127);				// 
	execve(attributes.pathname, attributes.argv, attributes.envp);
	err = errno;
	perror("minishell ");
	return (err);
}

int	child(t_cmd *cmd, t_minishell *minish)
{
	if (cmd->next)
		close_and_set(&cmd->next->input_fd);
	if (cmd->exit_s)
	{
		return (1);	// 
	}
	make_redirections(cmd);
	if (is_builtin(cmd->arguments->content))
		return (handle_builtin(cmd, minish));
	else
		return (exec_cmd(cmd, minish));
}

void	fork_cmd(t_cmd *cmd, t_minishell *minish, int stdfd[2])
{
	int	err;

	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("fork");
	if (cmd->pid == 0)
	{
		close(stdfd[0]);
		close(stdfd[1]);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		err = child(cmd, minish);
		exit(err);
	}
	close_and_set(&cmd->input_fd);
	close_and_set(&cmd->output_fd);
}
