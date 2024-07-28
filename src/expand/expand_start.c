/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:34:47 by egomez            #+#    #+#             */
/*   Updated: 2024/07/20 13:34:49 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expand_red(t_token *red, t_env *env, int exit_status)
{
	t_token	*tmp;
	t_list	*new_word;

	while (red)
	{
		tmp = red;
		new_word = NULL;
		handle_word(tmp->val, env, &new_word, exit_status);
		if (ft_lstsize(new_word) != 1)
			return (2);
		free(tmp->val);
		tmp->val = new_word->content;
		free(new_word);
		red = red->next;
	}
	return (0);
}

void	expand_var(t_minishell *minishell, int exit_s)
{
	t_list	*tmp_arg;
	t_token	*tmp_red;
	t_list	*new_arg;
	t_cmd	*cmd;

	cmd = minishell->commands;
	while (cmd)
	{
		new_arg = NULL;
		tmp_arg = cmd->arguments;
		tmp_red = cmd->redirections;
		while (tmp_red)
		{
			cmd->exit_s = expand_red(tmp_red, minishell->envi, exit_s);
			tmp_red = tmp_red->next;
		}
		while (tmp_arg)
		{
			handle_word(tmp_arg->content, minishell->envi, &new_arg, exit_s);
			tmp_arg = tmp_arg->next;
		}
		lstclear(&cmd->arguments);
		cmd->arguments = new_arg;
		cmd = cmd->next;
	}
}
