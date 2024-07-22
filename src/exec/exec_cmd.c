/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:40:39 by maamine           #+#    #+#             */
/*   Updated: 2024/07/21 20:34:59 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_cmd(t_cmd *cmd, t_minishell *minish)
{
	int				err;
	t_attributes	attributes;

	err = fill_attributes(&attributes, cmd->arguments, &minish->envi);
	free_minishell(minish);
	if (err || attributes.pathname[0] == 0)
	{
		free(attributes.pathname);
		free_achar(attributes.argv);
		free_achar(attributes.envp);
		return (err);
	}
	execve(attributes.pathname, attributes.argv, attributes.envp);
	err = errno;
	if (err == 13)
	{
		str_error_message(attributes.pathname, "Permission denied");
		return (126);
	}
	return (0);
}

int	child(t_cmd *cmd, t_minishell *minish, int stdfd[2])
{
	int	ret_builtin;

	if (cmd->next)
		close_and_set(&cmd->next->input_fd);
	if (cmd->exit_s)
		return (1);
	make_redirections(cmd);
	if (is_builtin(cmd->arguments->content))
	{
		ret_builtin = handle_builtin(cmd, minish, stdfd);
		free_minishell(minish);
		return (ret_builtin);
	}
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(stdfd[0]);
		close(stdfd[1]);
		err = child(cmd, minish, stdfd);
		exit(err);
	}
	close_and_set(&cmd->input_fd);
	close_and_set(&cmd->output_fd);
}
