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
#include <stdbool.h>

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

//while (s[i] != 0)
//{
//if (!tmp)
//tmp = ft_lstnew_empty();
//if (s[i] == '$')
//{
//dollar = 1;
//ft_lstadd_back(&tmp, ft_lstnew_empty());
//tmp = tmp->next;
//}
//if (s[i] == ' ' && dollar == 1)
//{
//dollar = 0;
//ft_lstadd_back(&tmp, ft_lstnew_empty());
//tmp = tmp->next;
//}
//tmp->content = ft_strjoin(tmp->content, &s[i]);
//i++;
//}

bool    is_delimiter(char c)
{
    if (ft_isalnum(c))
        return false;
    if (c == '_')
        return false;
    return true;
}

char	*ft_strjoin_char(char const *s1, char c)
{
    int		tot_size;
    char	*newchain;
    int i;

    if (!s1)
        return (NULL);
    tot_size = ft_strlen(s1) + 2;
    if (tot_size == 0)
        return (NULL);
    newchain = ft_calloc((size_t)tot_size, sizeof(char));
    if (newchain == NULL)
        return (NULL);
    i = 0;
    while (s1[i]) {
        newchain[i] = s1[i];
        i++;
    }
    newchain[i++] = c;
    newchain[i] = 0;
    return (newchain);
}

t_list  *split_in_lst(char *s)
{
    t_list  *first;
    t_list  *tmp;
    int     i;

    i = 0;
    first = ft_lstnew_empty();
    tmp = first;
    while (s[i])
    {
        if (i && is_delimiter(s[i]))
        {
            ft_lstadd_back(&tmp, ft_lstnew_empty());
            tmp = tmp->next;
        }
        tmp->content = ft_strjoin_char(tmp->content, s[i]);
        i++;
    }
    return (first);
}

void    changes(t_list *lst, t_env *envi)
{
	t_env	*copy_envi;
    char *env_to_find;

	while (lst)
    {
        copy_envi = envi;
        if (is_env(lst->content))
        {
            // while (tmp_envi && ft_strcmp(tmp_lst->content, tmp_envi->name))
            //     tmp_envi = tmp_envi->next;
            env_to_find = lst->content + 1;
            while (copy_envi)
            {
                if (ft_strcmp(env_to_find, copy_envi->name))
                {
                    copy_envi = copy_envi->next;
                    continue;
                }
                free(lst->content);
                lst->content = NULL;
                lst->content = ft_strdup(copy_envi->val);
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
    char    *result;

    result = ft_calloc(1, sizeof(char));
    while (lst)
    {
        result = ft_strjoin(result, lst->content);
        lst = lst->next;
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