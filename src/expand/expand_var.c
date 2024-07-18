/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:08:57 by egomez            #+#    #+#             */
/*   Updated: 2024/06/30 17:19:50 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_list	*split_in_lst(char *s)
{
	t_list	*first;
	t_list	*tmp;
	int		i;
	char	quote;
	bool	is_var;

	i = 0;
	quote = 0;
	is_var = (s[0] == '$' && s[1] && !is_delimiter(s[1]));
	first = ft_lstnew_empty();
	tmp = first;
	while (s[i])
	{
		if (quote == 0 && (s[i] == '\''|| s[i] == '"'))
			quote = s[i];
		else if(quote == s[i])
			quote = 0;
		if (i != 0 && quote != '\''
			&& (((!is_var && s[i] == '$' && s[i + 1] && (!is_delimiter(s[i + 1]) || (s[i + 1] == '?'))) || (s[i - 1] == '?' && s[i - 2] == '$'))
				|| (is_var
					&& (is_delimiter(s[i])
						&& !(s[i - 1] == '$' && s[i] == '?')))))
		{
			is_var = !is_var;
			ft_lstadd_back(&tmp, ft_lstnew_empty());
			tmp = tmp->next;
		}
		tmp->content = ft_strjoin_char(tmp->content, s[i], false);
		i++;
	}
	return (first);
}

static int	split_on_whitespace_aux(t_list **tmp, char *s)
{
	int	i;

	i = 0;
	while (s[i] && !is_whitespace(s[i])
		&& !(s[i] == '\'' || s[i] == '"') && (i <= 0 || s[i - 1] != '\\'))
	{
		(*tmp)->content = ft_strjoin_char((*tmp)->content, s[i], false);
		i++;
	}
	if (!is_whitespace(s[i]))
	{
		i--;
		return (i);
	}
	if (s[i])
	{
		lstadd_back(tmp, ft_lstnew_empty());
		*tmp = (*tmp)->next;
	}
	while (s[i] && is_whitespace(s[i]))
		i++;
	i--;
	return (i);
}

/**
 * `echo a  "" b"  c" `
 * turns into	`a  b c`
 * instead of	`a  b  c`
 */

static t_list	*split_on_whitespace(char *s)
{
	t_list	*first;
	t_list	*tmp;
	int		i;
	char	quote;

	i = 0;
	first = ft_lstnew_empty();
	tmp = first;
	quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && (i <= 0 || s[i - 1] != '\\'))
		{
			if (!quote)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
		}
		if (quote)
			tmp->content = ft_strjoin_char(tmp->content, s[i], false);
		else
			i += split_on_whitespace_aux(&tmp, s + i);
		i++;
	}
	return (first);
}

static void	changes_aux(t_list *lst, t_env *envi)
{
	char	*env_to_find;

	env_to_find = lst->content + 1;
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
		//lst->content = ft_strdup("");
	}
}

static void	changes(t_list *lst, t_env *envi, int exit_status)
{
	while (lst)
	{
		// if (is_env(lst->content))
		if (lst->content[0] == '$' && lst->content[1])
		{
			if (lst->content[1] != '?')
				changes_aux(lst, envi);
			else
				lst->content = ft_itoa(exit_status);
		}
		lst = lst->next;
	}
}

static char	*join_lst(t_list *lst)
{
	char	*result;

	result = ft_calloc(1, sizeof(char));
	while (lst)
	{
		if (lst->content)
			result = ft_strjoin(result, lst->content);
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
	//result = slash_quotes(result);
	// if (result[0] == '\0')
	// 	;	// Do whatever so that the node is deleted. To avoid `echo a $A` giving `a ` instead of `a`.
	splitted = split_on_whitespace(result);
	node = splitted;
	while (node)
	{
		node->content = supp_quotes(node->content);
		node = node->next;
	}
	lstadd_back(new, splitted);
	// while (splitted)
	// {
	// 	node = lstnew(splitted->content);
	// 	lstadd_back(new, node);
	// 	node = splitted;
	// 	splitted = splitted->next;
	// 	lstdelone(node);
	// }
}

static int	expand_red(t_token *red, t_env *env, int exit_status)
{
	t_token	*tmp;
	t_list	*new_word;

	while (red)
	{
		tmp = red;
		new_word = NULL;
		handle_word(tmp->val, env, &new_word, exit_status);
		if (ft_lstsize(new_word) != 1)
			return (2);
		tmp->val = new_word->content;
		red = red->next;
	}
	return (0);
}

void	expand_var(t_minishell *minishell, int exit_status)
{
	t_list	*tmp_arg;
	t_token	*tmp_red;
	t_list	*new_arg;
	t_cmd	*cmd;

	new_arg = NULL;
	cmd = minishell->commands;
	while (cmd)
	{
		tmp_arg = cmd->arguments;
		tmp_red = cmd->redirections;
		while (tmp_arg)
		{
			handle_word(tmp_arg->content, minishell->envi,
				&new_arg, exit_status);
			tmp_arg = tmp_arg->next;
		}
		lstclear(&cmd->arguments);
		cmd->arguments = new_arg;
		new_arg = NULL;
		while (tmp_red)
		{
			cmd->exit_s = expand_red(tmp_red, minishell->envi, exit_status);
			tmp_red = tmp_red->next;
		}
		cmd = cmd->next;
	}
}
