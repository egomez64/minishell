/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:36:18 by maamine           #+#    #+#             */
/*   Updated: 2024/06/24 17:39:08 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void unset_one(t_env **envi, char *name)
{
	t_env	*address;

	if ((*envi) == NULL)
		return ;
	if (ft_strcmp((*envi)->name, name) == 0)
	{
		address = (*envi)->next;
		free((*envi)->name);
		free((*envi)->val);
		*envi = address;
	}
	else
	{
		while (*envi && (*envi)->next && ft_strcmp((*envi)->next->name, name))
			envi = &(*envi)->next;

		if (*envi)
		{
			address = (*envi)->next->next;
			free((*envi)->next->name);
			free((*envi)->next->val);
			(*envi)->next = address;
		}
	}
}

void	unset(t_env *envi, t_list *args)
{
	args = args->next;
	while (args)
	{
		unset_one(&envi, args->content);
		args = args->next;
	}
}
