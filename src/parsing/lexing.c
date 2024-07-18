/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:43:35 by egomez            #+#    #+#             */
/*   Updated: 2024/07/18 15:57:11 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip(char *s, int *i)
{
	while (s[*i] != 0 && (s[*i] == ' ' || s[*i] == '\t'))
		(*i)++;
}

int	tokenize_word(t_token **tok_lst, char *val)
{
	t_token	*new_token;
	int		dquote;
	int		squote;
	char	*word;
	int		i;

	i = 0;
	dquote = 0;
	squote = 0;
	while (val[i] != 0)
	{
		if ((val[i] == ' ' || val[i] == '\t' || val[i] == '|' || val[i] == '>'
				|| val[i] == '<') && (dquote == 0 && squote == 0))
			break ;
		if (val[i] == '"' && (dquote == 1 || squote == 0))
			dquote = !dquote;
		else if (val[i] == '\'' && (squote == 1 || dquote == 0))
			squote = !squote;
		i++;
	}
	word = ft_substr(val, 0, i);
	new_token = token_new(word, WORD);
	token_add_back(tok_lst, new_token);
	return (i);
}

static void	add_symbol(t_token **tok_lst, char *symbol, int double_redirect)
{
	t_token	*new_token;

	if (symbol[0] == '<')
	{
		if (double_redirect == 1)
			new_token = token_new(symbol, HEREDOC);
		else
			new_token = token_new(symbol, INPUT);
	}
	else if (symbol[0] == '>')
	{
		if (double_redirect == 1)
			new_token = token_new(symbol, APPEND);
		else
			new_token = token_new(symbol, OUTPUT);
	}
	else
		new_token = token_new(symbol, PIPE);
	token_add_back(tok_lst, new_token);
}

int	tokenize_symbol(t_token **tok_lst, char *val)
{
	char	*symbol;
	int		i;
	int		double_redirect;

	double_redirect = 0;
	if ((val[0] == '<' && val[1] == '<') || (val[0] == '>' && val[1] == '>'))
	{
		double_redirect = 1;
		i = 2;
	}
	else
		i = 1;
	symbol = ft_substr(val, 0, i);
	add_symbol(tok_lst, symbol, double_redirect);
	return (i);
}

t_token	*lexer(char *arg)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	while (arg[i] != 0)
	{
		skip(arg, &i);
		if (arg[i] == '<' || arg[i] == '>' || arg[i] == '|')
			i += tokenize_symbol(&token, arg + i);
		else if (arg[i] != 0)
			i += tokenize_word(&token, arg + i);
	}
	return (token);
}
