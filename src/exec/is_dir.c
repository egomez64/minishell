/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:56:33 by maamine           #+#    #+#             */
/*   Updated: 2024/07/20 15:54:06 by maamine          ###   ########.fr       */
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

void	str_error_message(char *name, char *err)
{
	char	*str;
	int		name_len;
	int		err_len;

	name_len = ft_strlen(name);
	err_len = ft_strlen(err);
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

	if (stat(str, &buf) != 0)
	{
		str_error_message(str, strerror(errno));
		return (-1);
	}
	return (S_ISDIR(buf.st_mode));
}

int	check_name(char *str, char *envp_path)
{
	if (!is_path(str))
		return (locate_and_replace(str, envp_path));
	else if (is_dir(str))
	{
		str_error_message(str, "Is a directory");
		return (126);
	}
	else if (!access(str, X_OK))
	{
		str_error_message(str, "Permission denied");
		str_error_message(str, "No such file or directory");
		return (1);
	}
	return (0);
}
