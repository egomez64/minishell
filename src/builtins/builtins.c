/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:25:14 by egomez            #+#    #+#             */
/*   Updated: 2024/06/17 17:46:07 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtins(const char	*s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd") \
		|| !ft_strcmp(s, "export") || !ft_strcmp(s, "env") || !ft_strcmp(s, "unset") \
		|| !ft_strcmp(s, "exit"))
		return (true);
	return (false);
}

int	handle_builtins(t_cmd	*cmd)
{
	int	exit_status;

	if (cmd->arguments->content && !ft_strcmp(cmd->arguments->content, "pwd"))
		exit_status = pwd();
	return (exit_status);
}
