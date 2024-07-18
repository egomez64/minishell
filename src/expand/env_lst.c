/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:54:02 by egomez            #+#    #+#             */
/*   Updated: 2024/06/24 16:49:33 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*env_new(char	*var_name, char *var_val)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->name = var_name;
	new->val = var_val;
	return (new);
}

t_env	*env_last(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	env_add_back(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		env_last(*lst)->next = new;
	else
		*lst = new;
}

void	env_clear(t_env	*lst)
{
	if (lst->next != NULL)
		env_clear(lst->next);
	free(lst->name);
	free(lst->val);
	free(lst);
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
