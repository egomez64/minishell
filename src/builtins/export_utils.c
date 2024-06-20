/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:27:49 by egomez            #+#    #+#             */
/*   Updated: 2024/06/20 17:27:51 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>

int	check_arg(char *s)
{
	int	i;

	i = 0;
	if (s[0] >= '0' && s[0] <= '9')
		return (1);
	while(s[i] && s[i] != '=')
	{
		if (is_delimiter(s[i]))
			return (1);
		i++;
	}
	if (!s[i])
		return (1);
	return (0);
}