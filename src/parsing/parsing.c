/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:49:24 by egomez            #+#    #+#             */
/*   Updated: 2024/04/22 14:49:38 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redirect_tester(t_token **token)
{
	if ((*token)->next != NULL && (*token)->next->type != WORD)
		return (0);
	return (1);
}

int	pipe_tester(t_token **token)
{
	if ((*token)->next != NULL && (*token)->next->type == PIPE)
		return (0);
	return (1);
}

int parsing(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp->type == PIPE)
		return (0);
	while (tmp->next != NULL)
	{
		if (tmp->type == PIPE && !pipe_tester(&tmp))
			return (0);
		else if (tmp->type != WORD && tmp->type != PIPE && !redirect_tester(&tmp))
			return (0);
		tmp = tmp->next;
	}
	if (tmp->type == PIPE)
		return (0);
	return (1);
}