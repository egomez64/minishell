/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:49:24 by egomez            #+#    #+#             */
/*   Updated: 2024/07/03 18:45:23 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redirect_tester(t_token **token)
{
	if ((*token)->next == NULL || (*token)->next->type != WORD)
		return (0);
	return (1);
}

int	pipe_tester(t_token **token)
{
	if ((*token)->next == NULL || (*token)->next->type == PIPE)
		return (0);
	return (1);
}

int	parsing(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp->type == PIPE)
		return (0);
	while (tmp)
	{
		if (tmp->type == PIPE && !pipe_tester(&tmp))
			return (0);
		else if (tmp->type != PIPE && tmp->type != WORD
			&& !redirect_tester(&tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
