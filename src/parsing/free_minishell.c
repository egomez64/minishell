/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:59:09 by egomez            #+#    #+#             */
/*   Updated: 2024/06/30 17:20:52 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_minishell(t_minishell *minishell)
{
	minishell->commands = NULL;
	minishell->envi = NULL;
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->commands)
		cmd_clear(minishell->commands);
	if (minishell->envi)
		env_clear(minishell->envi);
}
