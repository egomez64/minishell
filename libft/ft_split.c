/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:39:28 by egomez            #+#    #+#             */
/*   Updated: 2023/11/16 18:27:42 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *s, char c)
{
	int	i;
	int	stat;
	int	words;

	i = 0;
	stat = 0;
	words = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && stat == 0)
		{
			stat = 1;
			words++;
		}
		else if (s[i] == c)
			stat = 0;
		i++;
	}
	return (words);
}

static char	*ft_worddup(const char	*s, char c, int *start)
{
	char	*word;
	int		old;

	while (s[*start] == c)
		(*start)++;
	old = *start;
	while (s[*start] != c && s[*start] != 0)
		(*start)++;
	word = ft_substr(s, old, *start - old);
	return (word);
}

static void	ft_freeresult(char **s, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_split(const char	*s, char c)
{
	char	**result;
	int		i;
	int		y;
	int		len;

	y = 0;
	if (!s)
		return (NULL);
	len = ft_countwords(s, c);
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = ft_worddup(s, c, &y);
		if (result[i] == NULL)
		{
			ft_freeresult(result, i);
			return (NULL);
		}
		i++;
	}
	return (result);
}
