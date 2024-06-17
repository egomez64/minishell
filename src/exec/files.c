/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:56:26 by maamine           #+#    #+#             */
/*   Updated: 2024/06/17 18:54:04 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error_open(char *path)	// 
{
	write(2, "error open:", 11);
	write(2, path, ft_strlen(path));
}

static int	open_input(t_exec *exec, t_token *redir)
{
	close_and_set(&exec->in_fd);
	if (redir->val && redir->val[0] != '\0')
		exec->in_fd = open(redir->val, O_RDONLY);
	if (exec->in_fd == -1)
		error_open(redir->val);
	return (exec->in_fd);
}


static int	open_output(t_exec *exec, t_token *redir)
{
	close_and_set(&exec->out_fd);
	if (redir->val && redir->val[0] != '\0')
		exec->out_fd = open(redir->val, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (exec->out_fd == -1)
		error_open(redir->val);
	return (exec->out_fd);
}

/// @brief Redirects an `oldfd` to a `newfd`,
// 		closing and reopenning it if necessary.
/// @param oldfd To be closed. The `int` will be set to `-1` once closed.
/// @param newfd Will point to the same file as `oldfd`.
// 		If open, will be closed and reopenned.
/// @return On success, these system calls return the new file descriptor.
// 		On error, -1 is returned
static int	redirect(int *oldfd, int newfd)
{
	int	fd;

	if (*oldfd == -1)
		return (-1);
	fd = dup2(*oldfd, newfd);
	if (fd == -1)
		perror("dup2");
	close_and_set(oldfd);
	return (fd);
}

int	make_redirections(t_exec *exec)
{
	int		err;
	t_token	*redir;

	err = 0;
	redir = exec->cmd->redirections;
	while (!err && redir)
	{
		if (redir->type == INPUT)
		{
			dprintf(3, "%d: input\n", getpid());
			err = open_input(exec, redir);
			dprintf(3, "%d: err = %d\n", getpid(), err);
		}
		else if (redir->type == OUTPUT)
		{
			dprintf(3, "%d: output\n", getpid());
			err = open_output(exec, redir);
			dprintf(3, "%d: err = %d\n", getpid(), err);
		}
		// else if (redir->type == HEREDOC)
		// 	err = open_heredoc(exec, redir);
		redir = redir->next;
	}
	if (err)
		return (err);
	err = redirect(&exec->in_fd, 0);
	if (err == -1)
		return (err);
	err = redirect(&exec->out_fd, 1);
	if (err == -1)
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
	{
		perror("pipe");
		return (err);
	}
	exec->out_fd = pipefd[1];
	exec->next->in_fd = pipefd[0];
	return (err);
}
