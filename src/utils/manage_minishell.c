/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:59:09 by egomez            #+#    #+#             */
/*   Updated: 2024/07/22 12:45:45 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern int	g_sig;

void	init_minishell(t_minishell *minishell, int ac, char **av, char **ep)
{
	g_sig = 0;
	(void) ac;
	(void) av;
	(*minishell).commands = NULL;
	(*minishell).envi = envp_to_lst(ep);
	(*minishell).exit_status = 0;
	(*minishell).n_line = 1;
}

void	close_mini_fds(t_cmd *cmd)
{
	while (cmd)
	{
		close_and_set(&cmd->input_fd);
		close_and_set(&cmd->output_fd);
		cmd = cmd->next;
	}
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->commands)
		cmd_clear(&minishell->commands);
	if (minishell->envi)
		env_clear(minishell->envi);
}
