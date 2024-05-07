/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:08:57 by egomez            #+#    #+#             */
/*   Updated: 2024/04/30 15:09:01 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list    *divide_lst(char *str)
{
	int		i;
	int		dollar;
	t_list	*lst;
	t_list	*current;

	dollar = 0;
	i = 0;
	current = NULL;
	lstadd_back(&current, lstnew(NULL));
	lst = current;
	while (str[i] != 0)
	{
		if (i > 0 && str[i] == '$' && dollar == 0)
		{
			dollar = 1;
			lstadd_back(&current, lstnew("$"));
		}
		else if (str[i] == ' ' && dollar == 1)
		{
			dollar = 0;
			lstadd_back(&current, lstnew(" "));
		}
		current->content = ft_strjoin(current->content, &str[i]);
		i++;
	}
	return (lst);
}

void	handle_cmd(t_cmd *node, t_env *table)
{
	t_list	*tmp_arg;
	t_token	*tmp_redirect;
	char	*transform;

	tmp_arg = NULL;
	tmp_redirect = NULL;
	if (node->arguments)
		tmp_arg = node->arguments;
	if (node->redirections)
		tmp_redirect = node->redirections;
	while (tmp_arg)
	{
		transform = node_treatment((char *)tmp_arg->content, table);
		if (transform)
		{
			free(tmp_arg->content);
			tmp_arg->content = transform;
		}
		tmp_arg = tmp_arg->next;
	}
	while (tmp_redirect)
	{
		transform = node_treatment((char *)tmp_redirect->val, table);
		if (transform)
		{
			free(tmp_redirect->val);
			tmp_redirect->val = transform;
		}
		tmp_redirect = tmp_redirect->next;
	}
}

void    expand_var(t_cmd *commands, t_env *env_var)
{
	t_cmd	*tmp;

	tmp = commands;
	while (tmp)
	{
		handle_cmd(tmp, env_var);
		tmp = tmp->next;
	}
}