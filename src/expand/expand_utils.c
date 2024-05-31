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

t_list	*ft_lstnew_empty()
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = malloc(sizeof(char));
	new->content[0] = 0;
	new->next = NULL;
	return (new);
}

int	is_env(char *s)
{
    int i;

    i = 0;
    while (s[i] != 0 && s[i] != '$')
        i++;
    if (s[i] != 0)
        return (1);
    return (0);
}

t_list  *split_in_lst(char *s)
{
    t_list  *result;
    t_list  *tmp;
    int     i;
    int     dollar;

    result = ft_lstnew_empty();
    tmp = result;
    i = 0;
    dollar = 0;
    while (s[i] != 0)
    {
        if (s[i] == '$')
        {
            dollar = 1;
            ft_lstadd_back(&tmp, ft_lstnew_empty());
            tmp = tmp->next;
        }
        if (s[i] == ' ' && dollar == 1)
        {
            dollar = 0;
            ft_lstadd_back(&tmp, ft_lstnew_empty());
            tmp = tmp->next;
        }
        tmp->content = ft_strjoin(tmp->content, &s[i]);
        i++;
    }
   
    return (result);
}

void    changes(t_list *lst, t_env *envi)
{
	t_env	*tmp_envi;
    t_list *tmp_lst;

    tmp_lst = lst;
    while (tmp_lst)
    {
        printf("content:%s\n", tmp_lst->content);
        tmp_lst = tmp_lst->next;
    }
    tmp_envi = envi;
    while (tmp_envi)
    {
        printf("name: %s value: %s\n", tmp_envi->name, tmp_envi->val);
        tmp_envi = tmp_envi->next;
    }

	while (lst)
    {
        tmp_envi = envi;
        if (is_env(lst->content))
        {
            // while (tmp_envi && ft_strcmp(tmp_lst->content, tmp_envi->name))
            //     tmp_envi = tmp_envi->next;
            while (tmp_envi)
            {
                if (ft_strcmp(lst->content, tmp_envi->name))
                {
                    tmp_envi = tmp_envi->next;
                    continue;
                }
                free(lst->content);
                lst->content = ft_strdup(tmp_envi->val);
                break;
            }
            // if (ft_strcmp(tmp_lst->content, tmp_envi->name))
            // {
            //     free(tmp_lst->content);
            //     tmp_lst->content = tmp_envi->val;
            // }
        }
        lst = lst->next;
    }
}

char    *join_lst(t_list *lst)
{
    t_list  *tmp_lst;
    char    *result;

    tmp_lst = lst;
    result = NULL;
    while (tmp_lst)
    {
        ft_strjoin(result, tmp_lst->content);
        tmp_lst = tmp_lst->next;
    }
    return (result);
}

char    *handle_var(char *s, t_env *envi)
{
	t_list	*splitted;
	char	*result;

	splitted = split_in_lst(s);
	changes(splitted, envi);
	result = join_lst(splitted);
	return (result);
}