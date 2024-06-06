/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:54:53 by egomez            #+#    #+#             */
/*   Updated: 2024/05/02 11:54:56 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*ft_lstnew_empty()
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = malloc(sizeof(char));
	new->content[0] = 0;
	new->next = NULL;
	return (new);
}

int	is_env(char *s)
{
    int i;

    i = 0;
    while (s[i] != 0 && s[i] != '$')
        i++;
    if (s[i] != 0)
        return (1);
    return (0);
}

bool    is_delimiter(char c)
{
    if (ft_isalnum(c))
        return false;
    if (c == '_')
        return false;
    return true;
}

char	*ft_strjoin_char(char const *s1, char c)
{
    int		tot_size;
    char	*newchain;
    int i;

    if (!s1)
        return (NULL);
    tot_size = ft_strlen(s1) + 2;
    if (tot_size == 0)
        return (NULL);
    newchain = ft_calloc((size_t)tot_size, sizeof(char));
    if (newchain == NULL)
        return (NULL);
    i = 0;
    while (s1[i]) {
        newchain[i] = s1[i];
        i++;
    }
    newchain[i++] = c;
    newchain[i] = 0;
    return (newchain);
}

char    *supp_quotes(char *join)
{
	char	*result;
	int		i;
	int		y;
	int		join_size;

	join_size = ft_strlen(join);
	result = ft_calloc(1, sizeof(char) * (join_size - 2));
	i = 1;
	y = 0;
	while (i < join_size - 1)
	{
		result[y] = join[i];
		y++;
		i++;
	}
	join = NULL;
	free(join);
	return (result);
}