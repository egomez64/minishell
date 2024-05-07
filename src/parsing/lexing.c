/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:43:35 by egomez            #+#    #+#             */
/*   Updated: 2024/04/18 18:43:36 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip(char *s, int *i)
{
    while (s[*i] != 0 && (s[*i] == ' ' || s[*i] == '\t'))
        (*i)++;
}

void	tokenize_word(t_token **tok_lst, char *val, int *i)
{
	int		dquote;
	int		squote;
	char	*tmp;
	int		old;

	old = *i;
	dquote = 0;
	squote = 0;
	while (val[*i] != 0)
	{
		if ((val[*i] == ' ' || val[*i] == '\t' || val[*i] == '|' ||
				val[*i] == '>' || val[*i] == '<') && (dquote == 0 && squote == 0))
			break;
		if (val[*i] == '"' && (dquote == 0 && squote == 0))
			dquote = 1;
		else if (val[*i] == '\'' && (dquote == 0 && squote == 0))
			squote = 1;
		else if (val[*i] == '"' && dquote == 1)
			dquote = 0;
		else if (val[*i] == '\'' && squote == 1)
			squote = 0;
		(*i)++;
	}
	tmp = ft_substr(val, old, *i - old);
	token_add_back(tok_lst, token_new(tmp, WORD));
}

void	tokenize_symbol(t_token **tok_lst, char *val, int *i)
{
	char	*tmp;
	int		old;
	int		double_redirect;

	old = *i;
	if (val[*i] == '<' && val[*i + 1] == '<')
	{
		double_redirect = 1;
		(*i) += 2;
	}
	else if (val[*i] == '>' && val[*i + 1] == '>')
	{
		double_redirect = 1;
		(*i) += 2;
	}
	else
		(*i) ++;
	tmp = ft_substr(val, old, *i - old);
	if (tmp[0] == '<')
	{
		if (double_redirect == 1)
			token_add_back(tok_lst, token_new(tmp, HEREDOC));
		else
			token_add_back(tok_lst, token_new(tmp, INPUT));
	}
	else if (tmp[0] == '>')
	{
		if (double_redirect == 1)
			token_add_back(tok_lst, token_new(tmp, APPEND));
		else
			token_add_back(tok_lst, token_new(tmp, OUTPUT));
	}
	else
		token_add_back(tok_lst, token_new(tmp, PIPE));
}

t_token	*lexer(char *arg)
{
	int	i;
	t_token	*token;

	i = 0;
	token = NULL;
	while(arg[i] != 0)
	{
		skip(arg, &i);
		if(arg[i] == '<' || arg[i] == '>' || arg[i] == '|')
			tokenize_symbol(&token, arg, &i);
		else if (arg[i] != 0)
			tokenize_word(&token, arg, &i);
	}
	return (token);
}