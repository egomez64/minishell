/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:25:14 by egomez            #+#    #+#             */
/*   Updated: 2024/06/27 11:31:30 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin(const char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "export") || !ft_strcmp(s, "unset")
		|| !ft_strcmp(s, "env") || !ft_strcmp(s, "exit"))
		return (true);
	return (false);
}

int	handle_builtin(t_cmd *cmd, t_minishell *minish)
{
	if (!cmd->arguments->content)
		return (1);	// A revoir
	if (!ft_strcmp(cmd->arguments->content, "echo"))
		return (echo(cmd));
	if (!ft_strcmp(cmd->arguments->content, "cd"))
		return (cd(cmd, minish->envi));
	if (!ft_strcmp(cmd->arguments->content, "pwd"))
		return (pwd());
	if (!ft_strcmp(cmd->arguments->content, "export"))
	{
		if (cmd->arguments->next)
			return (export_add(&minish->envi, cmd->arguments));
		else
			return (export(minish->envi));
	}
	if (!ft_strcmp(cmd->arguments->content, "unset"))
		unset(minish->envi, cmd->arguments);
	if (!ft_strcmp(cmd->arguments->content, "env"))
		return (env(minish->envi));
	if (!ft_strcmp(cmd->arguments->content, "exit"))
		return (__exit(cmd->arguments, minish->exit_status));
	return (0);
}
