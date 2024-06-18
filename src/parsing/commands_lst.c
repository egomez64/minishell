/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:40:09 by egomez            #+#    #+#             */
/*   Updated: 2024/06/18 17:40:52 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*cmd_new(void)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->arguments = NULL;
	new->redirections = NULL;
	new->exit_s = 0;
	new->input_fd = -1;
	new->output_fd = -1;
	return (new);
}

t_cmd	*cmd_last(t_cmd *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		cmd_last(*lst)->next = new;
	else
		*lst = new;
}

void	cmd_clear(t_cmd	*cmd)
{
	t_cmd	*next;

	if (cmd->arguments)
    	lstclear(&cmd->arguments);
	if (cmd->redirections)
    	token_clear(cmd->redirections);
	if (!cmd->next)
	{
		free(cmd);
		return ;
	}
	next = cmd->next;
	free(cmd);
	cmd_clear(next);
}