/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:56:26 by maamine           #+#    #+#             */
/*   Updated: 2024/06/06 15:31:15 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	make_redirections(t_exec *exec)
{
	int		err;
	t_token	*redir;

	err = 0;
	redir = exec->cmd->redirections;
	while (!err && redir)
	{
		if (redir->type == INPUT)
			err = redir_input(exec, redir);
		else if (redir->type == OUTPUT)
			err = redir_output(exec, redir);
		else if (redir->type == HEREDOC)
			err = redir_heredoc(exec, redir);
		redir = redir->next;
	}
	if (err)
		return (err);
	err = redirect(&exec->in_fd, 0);
	if (err)
		return (err);
	err = redirect(&exec->out_fd, 1);
	if (err)
		return (err);
	return (0);
}

int	open_pipe(t_exec *exec)
{
	int	pipefd[2];
	int	err;

	pipefd[0] = -1;
	pipefd[1] = -1;
	err = pipe(pipefd);
	if (err == -1)
		perror("pipe");
	exec->out_fd = pipefd[1];
	exec->next->in_fd = pipefd[0];
}
