/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:54:53 by egomez            #+#    #+#             */
/*   Updated: 2024/05/02 11:54:56 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		needed(char	*str, char *parent)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	if (count > 0)
	{
		i = 0;
		while (str[i] != 0 && (str[i] != '"' || str[i] != '\''))
			i++;
		*parent = str[i];
	}
	return (count);
}

char    *valof(t_env    *lst, char  *name)
{
	t_env   *tmp;

	tmp = lst;
	while (ft_strncmp(tmp->name, name, ft_strlen(name)) && tmp->next)
		tmp = tmp->next;
	if (ft_strncmp(tmp->name, name, ft_strlen(name)))
		return (NULL);
	return (tmp->val);
}

char	*get_name(char *str)
{
	int		i;
	int		y;
	char	*result;

	i = 1;
	y = 0;
	result = NULL;
	while (str[i] != 0)
	{
		result[y] = str[i];
		i++;
		y++;
	}
	result[y] = 0;
	return (result);
}

char    *node_treatment(char *str, t_env *lst)
{
    char    *result;
    t_list  *divide;
    t_list  *tmp;
    char    parent;

    result = NULL;
    parent = 0;
    if (needed(str, &parent))
	{
		divide = divide_lst(str);
        tmp = divide;
		while (divide->next)
		{
			if (tmp->content[0] == '$' && parent != '\'')
				result = ft_strjoin(result, valof(lst, get_name((char *)tmp->content)));
			result = ft_strjoin(result, tmp->content);
			tmp = tmp->next;
		}
	}
    lstclear(&divide);
    return (result);
}