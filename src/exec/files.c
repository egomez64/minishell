/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:56:26 by maamine           #+#    #+#             */
/*   Updated: 2024/06/30 15:12:49 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	make_redirections(t_cmd *cmd)
{
	int		err;

	err = 0;
	if (cmd->input_fd != 0)
	{
		// dprintf(3, "%d: redirect %d to 0\n", getpid(), cmd->input_fd);
		err = redirect(&cmd->input_fd, 0);
		if (err == -1)
			return (err);
		cmd->input_fd = 0;
	}
	if (cmd->output_fd != 1)
	{
		// dprintf(3, "%d: redirect %d to 1\n", getpid(), cmd->output_fd);
		err = redirect(&cmd->output_fd, 1);
		if (err == -1)
			return (err);
		cmd->output_fd = 1;
	}
	return (0);
}

int	open_pipe(t_cmd *cmd)
{
	int	pipefd[2];
	int	err;

	// dprintf(3, "open_pipe\n");
	pipefd[0] = -1;
	pipefd[1] = -1;
	err = pipe(pipefd);
	if (err == -1)
	{
		perror("pipe");
		return (err);
	}
	if (cmd->output_fd == -1)
	{
		cmd->output_fd = pipefd[1];
		// dprintf(3, "output_fd = %d\n", pipefd[1]);
	}
	else
	{
		close_and_set(pipefd + 1);
		// dprintf(3, "close pipefd[1]\n");
	}
	if (cmd->next->input_fd == -1)
	{
		cmd->next->input_fd = pipefd[0];
		// dprintf(3, "next->input_fd = %d\n", pipefd[0]);
	}
	else
	{
		close_and_set(pipefd + 0);
		// dprintf(3, "close pipefd[0]\n");
	}
	return (err);
}

int	dup_stdfd(int stdfd[2])
{
	stdfd[0] = dup(0);
	if (stdfd[0] == -1)
	{
		perror("dup2");
		return (1);
	}
	stdfd[1] = dup(1);
	if (stdfd[1] == -1)
	{
		perror("dup2");
		close(stdfd[0]);
		return (1);
	}
	return (0);
}

int	restore_stdfd(int stdfd[2])
{
	int	err;

	err = redirect(stdfd, 0);
	if (err)
		return (1);
	err = redirect(stdfd + 1, 1);
	if (err)
		return (1);
	return (0);
}
