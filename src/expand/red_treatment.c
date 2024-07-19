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

static void	error_message(char *path, int err)
{
	char	*str;
	char	*message;
	int		path_len;
	int		message_len;

	message = strerror(err);
	if (!message)
		return ;
	path_len = ft_strlen(path);
	message_len = ft_strlen(message);
	str = malloc((15 + path_len + message_len) * sizeof (char));
	if (!str)
		return ;
	ft_strlcpy(str, "minishell: ", 12);
	ft_strlcpy(str + 11, path, path_len + 1);
	ft_strlcpy(str + 11 + path_len, ": ", 3);
	ft_strlcpy(str + 13 + path_len, message, message_len + 1);
	ft_strlcpy(str + 13 + path_len + message_len, "\n", 2);
	write(2, str, ft_strlen(str));
	free(str);
}

void	red_treatment(t_minishell *minishell)
{
	t_token	*redir;
	t_cmd	*cmd;
	int		err;

	cmd = minishell->commands;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir && !cmd->exit_s)
		{
			if (redir->type == HEREDOC && g_sig != SIGINT)
				handle_heredoc(redir->val, &cmd->input_fd, &cmd->exit_s,
					minishell->n_line);
			else if (redir->type == INPUT)
				err = handle_input(redir->val, &cmd->input_fd, &cmd->exit_s);
			else if (redir->type == APPEND)
				err = handle_append(redir->val, &cmd->output_fd, &cmd->exit_s);
			else if (redir->type == OUTPUT)
				err = handle_output(redir->val, &cmd->output_fd, &cmd->exit_s);
			if (cmd->exit_s && cmd->exit_s != 130)
				error_message(redir->val, err);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
