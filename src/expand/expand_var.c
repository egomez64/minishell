/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:08:57 by egomez            #+#    #+#             */
/*   Updated: 2024/07/18 17:27:28 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	expand_one_var(t_list *lst, t_env *envi, char *env_to_find)
{
	while (envi)
	{
		if (ft_strcmp(env_to_find, envi->name))
		{
			envi = envi->next;
			continue ;
		}
		free(lst->content);
		lst->content = NULL;
		if (envi->val)
		{
			lst->content = ft_strdup(envi->val);
			lst->content = slash_quotes(lst->content);
		}
		break ;
	}
	if (!envi)
	{
		free(lst->content);
		lst->content = NULL;
	}
}

static void	changes(t_list *lst, t_env *envi, int exit_status)
{
	char	*env_to_find;
	int		i;

	while (lst)
	{
		i = 1;
		if ((lst->content[0] == '$' && lst->content[1])
			&& (!is_delimiter(lst->content[1]) || lst->content[1] == '?'))
		{
			if (lst->content[1] != '?')
			{
				while (!is_delimiter(lst->content[i]))
					i++;
				env_to_find = ft_substr(lst->content, 1, i - 1);
				expand_one_var(lst, envi, env_to_find);
				free (env_to_find);
			}
			else
			{
				free(lst->content);
				lst->content = ft_itoa(exit_status);
			}
		}
		lst = lst->next;
	}
}

static char	*join_lst(t_list *lst)
{
	char	*result;
	char	*tmp;

	result = ft_calloc(1, sizeof(char));
	while (lst)
	{
		if (lst->content)
		{
			tmp = ft_strjoin(result, lst->content);
			free(result);
			if (!tmp)
				return (NULL);
			result = tmp;
		}
		lst = lst->next;
	}
	return (result);
}

static int	is_split_empty(t_list *splitted)
{
	while (splitted)
	{
		if (splitted->content)
			return (0);
		splitted = splitted->next;
	}
	return (1);
}

void	handle_word(char *s, t_env *envi, t_list **new, int exit_status)
{
	t_list	*splitted;
	char	*result;
	t_list	*node;

	splitted = split_in_lst(s);
	changes(splitted, envi, exit_status);
	if (is_split_empty(splitted))
	{
		lstclear(&splitted);
		return ;
	}
	result = join_lst(splitted);
	lstclear(&splitted);
	result = supp_dollars(result);
	splitted = split_on_whitespace(result);
	free(result);
	node = splitted;
	while (node)
	{
		node->content = supp_quotes(node->content);
		node = node->next;
	}
	lstadd_back(new, splitted);
}
