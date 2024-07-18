/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:03:45 by egomez            #+#    #+#             */
/*   Updated: 2024/07/18 16:01:24 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_token(t_token **token, t_cmd **commands, t_cmd **current)
{
	t_token	*new;
	t_token	*prev;

	if ((*token)->type == WORD)
		lstadd_back(&(*current)->arguments, lstnew((*token)->val));
	else if ((*token)->type == PIPE)
	{
		free((*token)->val);
		(*current) = cmd_new();
		cmd_add_back(commands, (*current));
	}
	else
	{
		new = token_new((*token)->next->val, (*token)->type);
		token_add_back(&(*current)->redirections, new);
		prev = *token;
		*token = (*token)->next;
		free(prev->val);
		free(prev);
	}
}

t_cmd	*cmd(t_token *token)
{
	t_cmd	*commands;
	t_cmd	*current;
	t_token	*prev;

	commands = NULL;
	if (token)
	{
		current = cmd_new();
		cmd_add_back(&commands, current);
	}
	while (token)
	{
		add_token(&token, &commands, &current);
		prev = token;
		token = token->next;
		free(prev);
	}
	return (commands);
}

// t_cmd	*cmd(t_token **token)
// {
// 	t_cmd	*commands;
// 	t_token	*tmp;
// 	t_arg	*last;
// 	t_cmd	*current;
// 
// 	commands = NULL;
// 	tmp = *token;
// 	if (tmp)
// 	{
// 		current = cmd_new();
// 		cmd_add_back(&commands, current);
// 	}
// 	while (tmp)
// 	{
// 		if (tmp->type == WORD)
// 		{
// 			lstadd_back(&current->arguments, lstnew(tmp->val));
// 			last = &tmp->type;
// 		}
// 		else if (tmp->type == PIPE)
// 		{
// 			current = cmd_new();
// 			cmd_add_back(&commands, current);
// 		}
// 		else
// 		{
// 			token_add_back(&current->redirections,
// 				token_new(tmp->next->val, tmp->type));
// 			last = &tmp->type;
// 			tmp = tmp->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (commands);
// }
