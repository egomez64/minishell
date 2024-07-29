/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:41:58 by egomez            #+#    #+#             */
/*   Updated: 2024/07/03 18:27:37 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_sig;

static int	handle_input(char *path, int *fd, int *exit_s)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	*fd = open(path, O_RDONLY, 0666);
	if (*fd < 0)
	{
		*exit_s = 1;
		return (errno);
	}
	return (0);
}

static int	handle_append(char *path, int *fd, int *exit_s)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	*fd = open(path, O_APPEND | O_RDWR | O_CREAT, 0666);
	if (*fd < 0)
	{
		*exit_s = 1;
		return (errno);
	}
	return (0);
}

static int	handle_output(char *path, int *fd, int *exit_s)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	*fd = open(path, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (*fd < 0)
	{
		*exit_s = 1;
		return (errno);
	}
	return (0);
}

void	red_treatment(t_minishell *minishell)
{
	t_token	*redir;
	t_cmd	*cmd;
	int		err;

	heredoc_treatment(minishell);
	if (minishell->commands->exit_s != 0)
		return ;
	cmd = minishell->commands;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir && !cmd->exit_s)
		{
			if (redir->type == INPUT)
				err = handle_input(redir->val, &cmd->input_fd, &cmd->exit_s);
			else if (redir->type == APPEND)
				err = handle_append(redir->val, &cmd->output_fd, &cmd->exit_s);
			else if (redir->type == OUTPUT)
				err = handle_output(redir->val, &cmd->output_fd, &cmd->exit_s);
			if (cmd->exit_s)
				error_message(redir->val, err);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

bool	check_heredoc_quote(t_cmd *cmd)
{
	t_token	*tmp;
	int		i;

	i = 0;
	while (cmd)
	{
		while (cmd->redirections)
		{
			if (cmd->redirections->type == HEREDOC)
				tmp = cmd->redirections;
			cmd->redirections = cmd->redirections->next;
		}
		cmd = cmd->next;
	}
	while (tmp->val && tmp->val[i]
		&& (tmp->val[i] != '\'' && tmp->val[i] != '"'))
		i++;
	if (tmp->val[i] == 0)
		return (true);
	return (false);
}
