/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:56:33 by maamine           #+#    #+#             */
/*   Updated: 2024/07/14 18:55:15 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_path(char *str)
{
	int	i;

	if (str[0] == '/' || ft_strncmp(str, "./", 2) == 0)
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] == '/' && str[i - 1] != '\\')
			return (1);
		i++;
	}
	return (0);
}

int	is_dir(char *str)
{
	struct stat	buf;

	if (!is_path(str))
		return (0);
	if (stat(str, &buf))
		return (-1);
	return (S_ISDIR(buf.st_mode));
}

int	check_name(char *str, int *err)
{
	(void) str;
	(void) err;
	return (0);
}
