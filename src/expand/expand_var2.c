/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:43:30 by egomez            #+#    #+#             */
/*   Updated: 2024/07/20 12:43:34 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	void	check_for_expand(char *quote, char c)
{
	if (*quote == 0 && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

static	int	check_before_split(char quote, bool is_var, int i, char *s)
{
	if ((i != 0 && quote != '\''
			&& (((!is_var && s[i] == '$' && s[i + 1]
						&& (!is_delimiter(s[i + 1]) || (s[i + 1] == '?')))
					|| (s[i - 1] == '?' && s[i - 2] == '$'))
				|| (is_var
					&& (is_delimiter(s[i])
						&& !(s[i - 1] == '$' && s[i] == '?')))))
		|| (is_var && (s[i] == '\'' || s[i] == '"')))
		return (1);
	return (0);
}

t_list	*split_in_lst(char *s)
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
		check_for_expand(&quote, s[i]);
		if (check_before_split(quote, is_var, i, s))
		{
			is_var = !is_var;
			ft_lstadd_back(&tmp, ft_lstnew_empty());
			tmp = tmp->next;
		}
		tmp->content = ft_strjoin_char(tmp->content, s[i], true);
		i++;
	}
	return (first);
}

static	int	split_on_whitespace_aux(t_list **tmp, char *s)
{
	int	i;

	i = 0;
	while (s[i] && !is_whitespace(s[i])
		&& (!(s[i] == '\'' || s[i] == '"') || (i != 0 && s[i - 1] == '\\')))
	{
		(*tmp)->content = ft_strjoin_char((*tmp)->content, s[i], true);
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

t_list	*split_on_whitespace(char *s)
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
			tmp->content = ft_strjoin_char(tmp->content, s[i], true);
		else
			i += split_on_whitespace_aux(&tmp, s + i);
		i++;
	}
	return (first);
}
