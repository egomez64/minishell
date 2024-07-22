/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:15:25 by maamine           #+#    #+#             */
/*   Updated: 2024/07/22 12:23:03 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	str_skip_to_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	is_in(char c, char *targets)
{
	int	i;

	i = 0;
	while (targets[i] && c != targets[i])
		i++;
	return (c == targets[i]);
}

int	str_skip_to_any_char(char *str, char *targets)
{
	int	i;

	i = 0;
	while (str[i] && !is_in(str[i], targets))
		i++;
	return (i);
}
