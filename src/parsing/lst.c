/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:10:36 by egomez            #+#    #+#             */
/*   Updated: 2024/07/18 14:51:02 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*lstnew(char *val)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->content = val;
	new->next = NULL;
	return (new);
}

t_list	*lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		lstlast(*lst)->next = new;
	else
		*lst = new;
}

void	lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	free(lst->content);
	free(lst);
}

void	lstclear(t_list **lst)
{
	if (!lst && !(*lst))
		return ;
	if (*lst && (*lst)->next)
		lstclear(&(*lst)->next);
	lstdelone(*lst);
	*lst = NULL;
}
