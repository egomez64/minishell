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

t_list  *split_on_whitespace(char *s)
{
    t_list  *first;
    t_list  *tmp;
    int     i;
    char quote;
    i = 0;
    first = ft_lstnew_empty();
    tmp = first;
    quote = 0;
    if (s[0] == '\'' || s[0] == '"')
        quote = s[0];
    while (s[i])
    {
        if ((s[i] == '\'' || s[i] == '"') && (i > 0 && s[i - 1] != '\\'))
        {
            if (quote && quote == s[i])
                quote = 0;
            else if (!quote)
                quote = s[i];
        }
        if (quote)
            tmp->content = ft_strjoin_char(tmp->content, s[i]);
        else
        {
            while (s[i] && !is_whitespace(s[i]))
            {
                tmp->content = ft_strjoin_char(tmp->content, s[i]);
                i++;
            }
            if (s[i])
            {
                lstadd_back(&tmp, ft_lstnew_empty());
                tmp = tmp->next;
            }
            while (s[i] && is_whitespace(s[i]))
                i++;
            continue;
        }
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
                lst->content = slash_quotes(lst->content);
                break;
            }
            if (!copy_envi)
            {
                free(lst->content);
                lst->content = NULL;
                lst->content = ft_strdup("");
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

int expand_red(t_token *red, t_env *env)
{
    t_token *tmp;
    t_list *new_word;
    while (red)
    {
        tmp = red;
        new_word = NULL;
        handle_word(tmp->val, env, &new_word);
        if (ft_lstsize(new_word) != 1)
            return (0); //ambigous redirect
        tmp->val = new_word->content;
        red = red->next;
    }
    return (1);
}


void    handle_word(char *s, t_env *envi, t_list **new)
{
	t_list	*splitted;
	char	*result;
    t_list  *node;

    splitted = split_in_lst(s);
	changes(splitted, envi);
	result = join_lst(splitted);
    splitted = split_on_whitespace(result);
    node = splitted;
    while (node)
    {
        node->content = supp_quotes(node->content);
        node = node->next;
    }
    while (splitted)
    {
        node = lstnew(splitted->content);
        lstadd_back(new, node);
        node = splitted;
        splitted = splitted->next;
        lstdelone(node);
    }
}

void	expand_var(t_cmd **commands, t_env **env_var)
{
    t_cmd   *tmp_cmd;
    t_list  *tmp_arg;
    t_token *tmp_red;
    t_list  *new_arg;

    tmp_cmd = *commands;
    new_arg = NULL;
    while(tmp_cmd)
    {
        tmp_arg = tmp_cmd->arguments;
        tmp_red = tmp_cmd->redirections;
        while(tmp_arg)
        {
            handle_word(tmp_arg->content, *env_var, &new_arg);
            tmp_arg = tmp_arg->next;
        }
        lstclear(&tmp_cmd->arguments);
        tmp_cmd->arguments = new_arg;
        while(tmp_red)
        {
            expand_red(tmp_red, *env_var);
            tmp_red = tmp_red->next;
        }
        tmp_cmd = tmp_cmd->next;
    }
}
