/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:43:24 by egomez            #+#    #+#             */
/*   Updated: 2024/06/26 14:58:05 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	how_many_q(char *arg)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
			nb++;
		i++;
	}
	return (nb);
}

char	*slash_quotes(char *arg)
{
	int		nb_quotes;
	int		i;
	int		y;
	char	*result;

	nb_quotes = how_many_q(arg);
	i = 0;
	y = 0;
	if (!nb_quotes)
		return (arg);
	result = ft_calloc(ft_strlen(arg) + nb_quotes + 1, sizeof(char));
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
		{
			result[y] = '\\';
			y++;
		}
		result[y] = arg[i];
		y++;
		i++;
	}
	free(arg);
	return (result);
}

static int	cpy(char *result, char *join, char *quote)	// To rename
{
	int	i;

	i = 0;
	if (*quote == 0 && (join[i] == '"' || join[i] == '\''))
	{
		*quote = join[i];
		i++;
	}
	else if (*quote == join[i])
	{
		*quote = 0;
		i++;
		return (i);
	}
	 if (join[i] == '\\' && (join[i + 1] == '\'' || join[i + 1] == '"'))
	 	i++;
	*result = join[i];
	i++;
	return (i);
}

char	*supp_quotes(char *join)
{
	char	*result;
	char	quote;
	int		i;
	int		y;
	int		len_join;

	len_join = ft_strlen(join);
	result = ft_calloc((len_join + 1), sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	y = 0;
	quote = 0;
	while (i < len_join)
	{
		i += cpy(result + y, join + i, &quote);
		y++;
	}
	result[i] = '\0';
	free(join);
	return (result);
}
