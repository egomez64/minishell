/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:25:14 by egomez            #+#    #+#             */
/*   Updated: 2024/06/24 17:36:38 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtins(const char	*s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "export") || !ft_strcmp(s, "env")
		|| !ft_strcmp(s, "unset") || !ft_strcmp(s, "exit"))
		return (true);
	return (false);
}

int	handle_builtins(t_cmd	*cmd, t_env **envi)
{
	int	exit_s;

	exit_s = 0;
	if (!cmd->arguments->content)
		return (1);	// A revoir
	if (!ft_strcmp(cmd->arguments->content, "pwd"))
		exit_s = pwd();
	else if (!ft_strcmp(cmd->arguments->content, "env"))
		exit_s = env(*envi);
	else if (!ft_strcmp(cmd->arguments->content, "export"))
	{
		if (cmd->arguments->next)
			exit_s = export_add(envi, cmd->arguments);
		else
			exit_s = export(*envi);
	}
	else if (cmd->arguments->next
		&& !ft_strcmp(cmd->arguments->content, "unset"))
		unset(*envi, cmd->arguments->next->content);
	else if (!ft_strcmp(cmd->arguments->content, "echo"))
		exit_s = echo(cmd);
	return (exit_s);
}
