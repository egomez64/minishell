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

void	unset(t_env *envi, char *s)
{
	t_env	**adress;

	while (envi)
	{
		if (envi->next && !ft_strcmp(envi->next->name, s))
		{
			adress = &envi->next;
			envi = envi->next;
			if (envi->next)
				*adress = envi->next;
			else
				*adress = NULL;
			free(envi->name);
			free(envi->val);
			break ;
		}
		envi = envi->next;
	}
	return ;
}
