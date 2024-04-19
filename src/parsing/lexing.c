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

#include <parsing.h>

const static char * arg_to_string[] = {
	[WORD] = "Word",
	[PIPE] = "Pipe",
	[L_REDIRECT] = "L_Redirect",
	[R_REDIRECT] = "R_Redirect",
};

void	skip(char *s, int *i)
{
    while (s[*i] != 0 && (s[*i] == ' ' || s[*i] == '\t'))
        (*i)++;
}

// cat|dc
// "acb"ab'xd'
// aaabccc'd | d'
// "echo abc"
// 'xddd "dsada    '
void	tokenize_word(t_token **tok_lst, char *val, int *i)
{
	int		quote;
	char	*tmp;
	int		old;

	old = *i;
	while (val[*i] != 0)
	{
		if ((val[*i] == ' ' || val[*i] == '\t' || val[*i] == '|' ||
				val[*i] == '>' || val[*i] == '<') && quote == 0)
			break;
		if ((val[*i] == '"' || val[*i] == '\'') && quote == 0)
			quote = 1;
		else if ((val[*i] == '"' || val[*i] == '\'') && quote == 1)
			quote = 0;
		(*i)++;
	}
	tmp = ft_substr(val, old, *i - old);
	token_add_back(tok_lst, token_new(tmp, WORD));
}

void	tokenize_symbol(t_token **tok_lst, char *val, int *i)
{
	char	*tmp;
	int		old;

	old = *i;
	if (val[*i] == '<' && val[*i + 1] == '<')
		(*i) += 2;
	else if (val[*i] == '>' && val[*i + 1] == '>')
		(*i) += 2;
	else
		(*i) ++;
	tmp = ft_substr(val, old, *i - old);
	if (tmp[0] == '<')
		token_add_back(tok_lst, token_new(tmp, L_REDIRECT));
	else if (tmp[0] == '>')
		token_add_back(tok_lst, token_new(tmp, R_REDIRECT));
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
		else
			tokenize_word(&token, arg, &i);
	}
	return (token);
}

int	main(int ac, char **av)
{
	t_token *test;
	(void)ac;

	test = lexer(av[1]);
	while(test->next != 0)
	{
		printf("(%s) : (%s)\n", arg_to_string[test->type], test->val);
		test = test->next;
	}
	printf("(%s) : (%s)\n", arg_to_string[test->type], test->val);
}