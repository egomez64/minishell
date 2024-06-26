/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:27:49 by egomez            #+#    #+#             */
/*   Updated: 2024/06/26 19:16:14 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**sep_on_equal(char *s)
{
	char	**new;
	int		i;
	int		y;

	i = 0;
	y = 0;
	new = ft_calloc(3, sizeof(char *));
	while (s[i] && s[i] != '=')
		i++;
	new[0] = ft_substr(s, 0, i);
	i++;
	y = i;
	while (s[i])
		i++;
	new[1] = ft_substr(s, y, i - y);
	return (new);
}
