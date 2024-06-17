/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:41:58 by egomez            #+#    #+#             */
/*   Updated: 2024/06/14 17:42:00 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_input(char *path, int *fd, int *exit_s)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	*fd = open(path, O_RDONLY, 0666);
	if (*fd < 0)
		*exit_s = 1;
}

void	handle_append(char *path, int *fd, int *exit_s)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}

	*fd = open(path, O_APPEND | O_RDWR | O_CREAT, 0666);
	if (*fd < 0)
		*exit_s = 1;
}

void	handle_output(char *path, int *fd, int *exit_s)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	*fd = open(path, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (*fd < 0)
		*exit_s = 1;
}

void	red_treatment(t_cmd **lst_cmd)
{
	t_token	*tmp_red;
	t_cmd	*cmd;

	cmd = *lst_cmd;
	while (cmd)
	{
		tmp_red = cmd->redirections;
		while (tmp_red)
		{
			if (tmp_red->type == HEREDOC)
				handle_heredoc(tmp_red->val, &cmd->input_fd, &cmd->exit_s);
			if (tmp_red->type == INPUT)
				handle_input(tmp_red->val, &cmd->input_fd, &cmd->exit_s);
			if (tmp_red->type == APPEND)
				handle_append(tmp_red->val, &cmd->output_fd, &cmd->exit_s);
			if (tmp_red->type == OUTPUT)
				handle_output(tmp_red->val, &cmd->output_fd, &cmd->exit_s);
			tmp_red = tmp_red->next;
		}
		cmd = cmd->next;
	}
}