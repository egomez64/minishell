/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:56:33 by maamine           #+#    #+#             */
/*   Updated: 2024/07/19 15:16:26 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * No '/':
 * 		is a command, look through PATH
 * Has '/':
//  * 		Has "./":
//  * 			is a relative path
//  * 		Else
//  * 			is an absolute path
 * 		is a path.
 * 		is dir:
 * 			Error.
 * 		is not dir:
 * 			try to execute.
 */

static void	error_message(char *name, char *err)
{
	char	*str;
	int		name_len;
	int		err_len;

	str = malloc((name_len + err_len + 15) * sizeof (char));
	if (!str)
		return ;
	ft_strlcpy(str, "minishell: ", 12);
	ft_strlcpy(str + 11, name, name_len + 1);
	ft_strlcpy(str + name_len + 11, ": ", 3);
	ft_strlcpy(str + name_len + 13, err, err_len + 1);
	ft_strlcpy(str + name_len + err_len + 13, "\n", 2);
	write(2, str, name_len + err_len + 15);
	free(str);
}

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
	if (stat(str, &buf) != 0)
	{
		error_message(str, strerror(errno));
		return (-1);
	}
	return (S_ISDIR(buf.st_mode));
}

int	check_name(char *str)
{
	int	dir;

	if (!is_path(str))
	{
		;	// Find command through PATH
		error_message(str, "command not found");
		return (127);
	}
	else if (is_dir(str))
	{
		error_message(str, "Is a directory");
		return (126);
	}
	else if (!access(str, X_OK))
	{
		error_message(str, "Permission denied");
		error_message(str, "No such file or directory");
		return (1);
	}
	return (0);
}
