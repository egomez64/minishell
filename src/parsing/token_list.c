/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:47:38 by egomez            #+#    #+#             */
/*   Updated: 2024/04/19 14:47:41 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_token	*token_new(char	*val, t_arg type)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->val = val;
	new->type = type;
	return (new);
}

t_token	*token_last(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	token_add_back(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		token_last(*lst)->next = new;
	else
		*lst = new;
}