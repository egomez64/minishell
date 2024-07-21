/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:56:33 by maamine           #+#    #+#             */
/*   Updated: 2024/07/21 18:43:31 by maamine          ###   ########.fr       */
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

int	is_dir(char *str, int print_error)
{
	struct stat	buf;
	int			dir;

	if (stat(str, &buf) != 0)
	{
		if (print_error)
			str_error_message(str, strerror(errno));
		return (1);
	}
	dir = S_ISDIR(buf.st_mode);
	if (dir)
		str_error_message(str, "Is a directory");
	return (dir);
}

static int	file_status(char *str)
{
	struct stat	buf;
	int			err;

	if (stat(str, &buf) != 0)
	{
		err = errno;
		str_error_message(str, strerror(err));
		// return (127);
		return (err);
	}
	if (S_ISDIR(buf.st_mode))
		str_error_message(str, "Is a directory");
	// else if ((__S_IREAD | __S_IEXEC) & buf.st_mode)
	else if ((buf.st_mode & (S_IRUSR | S_IXUSR)) != (S_IRUSR | S_IXUSR))
		str_error_message(str, "Permission denied");
	return (126);
}

int	check_name(char **str, char *envp_path)
{
	if (!is_path(*str))
		return (locate_and_replace(str, envp_path));
	return (file_status(*str));
	// else if (is_dir(*str, 1))
	// {
	// 	return (127);
	// }
	// else if (access(*str, X_OK) != 0)
	// {
	// 	str_error_message(*str, "Permission denied");
	// 	str_error_message(*str, "No such file or directory");
	// 	return (126);
	// }
	// return (0);
}
