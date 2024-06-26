/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:25:14 by egomez            #+#    #+#             */
/*   Updated: 2024/06/26 18:40:29 by maamine          ###   ########.fr       */
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

int	handle_builtins(t_minishell *minish)
{
	if (!minish->commands->arguments->content)
		return (1);	// A revoir
	if (!ft_strcmp(minish->commands->arguments->content, "echo"))
		return (echo(minish->commands));
	if (!ft_strcmp(minish->commands->arguments->content, "cd"))
		return (cd(minish->commands, minish->envi));
	if (!ft_strcmp(minish->commands->arguments->content, "pwd"))
		return (pwd());
	if (!ft_strcmp(minish->commands->arguments->content, "export"))
	{
		if (minish->commands->arguments->next)
			return (export_add(&minish->envi, minish->commands->arguments));
		else
			return (export(minish->envi));
	}
	if (!ft_strcmp(minish->commands->arguments->content, "unset"))
		unset(minish->envi, minish->commands->arguments);
	if (!ft_strcmp(minish->commands->arguments->content, "env"))
		return (env(minish->envi));
	if (!ft_strcmp(minish->commands->arguments->content, "exit"))
		return (__exit(minish->commands->arguments, minish->exit_status));
	return (0);
}
