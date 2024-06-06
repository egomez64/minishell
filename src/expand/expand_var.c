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

    result = NULL;
    if (s[0] != '\'')
    {
        splitted = split_in_lst(s);
	    changes(splitted, envi);
	    result = join_lst(splitted);
    }
    if (result && (result[0] == '\'' || result[0] == '"'))
        result = supp_quotes(result);
    else if (!result && (s[0] == '\'' || s[0] == '"'))
        result = supp_quotes(s);
    return (result);
}

void	expand_var(t_cmd **commands, t_env **env_var)
{
    t_cmd   *tmp_cmd;
    t_list  *tmp_arg;
    t_token *tmp_red;

    tmp_cmd = *commands;
    while(tmp_cmd)
    {
        tmp_arg = tmp_cmd->arguments;
        tmp_red = tmp_cmd->redirections;
        while(tmp_arg)
        {
            tmp_arg->content = handle_var(tmp_arg->content, *env_var);
            tmp_arg = tmp_arg->next;
        }
        while(tmp_red)
        {
            tmp_red->val = handle_var(tmp_red->val, *env_var);
            tmp_red = tmp_red->next;
        }
        tmp_cmd = tmp_cmd->next;
    }
}