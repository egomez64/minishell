/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:43:24 by egomez            #+#    #+#             */
/*   Updated: 2024/06/07 13:43:26 by egomez           ###   ########.fr       */
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

char    *slash_quotes(char *arg)
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
	arg = NULL;
	free(arg);
	return (result);
}

char    *supp_quotes(char *join)
{
	char	*result;
	char    quote;
    int     i;
    int     y;
	int		join_size;

	join_size = ft_strlen(join);
	result = ft_calloc(1, sizeof(char) * (join_size));
	i = 0;
	y = 0;
    quote = 0;
	while (i < join_size)
	{
        if (quote == 0 && (join[i] == '"' || join[i] == '\''))
			quote = join[i++];
		if (quote == join[i])
		{
			quote = 0;
			i++;
			continue;
       	}
		if (join[i] == '\\')
			i++;
		result[y++] = join[i++];
	}
	join = NULL;
	free(join);
	return (result);
}
