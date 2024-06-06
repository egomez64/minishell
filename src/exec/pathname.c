/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:11:19 by maamine           #+#    #+#             */
/*   Updated: 2024/06/06 16:16:44 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief Creates a `struct` to manage `string` allocations.
// 		Does not duplicate a `string`.
/// @param str The `string` to manage.
/// @return A `t_string`, with the `string`
// 		and its allocated size (`-1` if nothing allocated).
static t_string	create_t_string(char *str)
{
	t_string	string;

	string.ptr = str;
	if (!str)
		string.size = -1;
	else
		string.size = ft_strlen(str) + 1;
	return (string);
}

/// @brief Generates a `pathname` from a path and an executable.
/// @return Number of characters to jump to get to the next path
// 		in `envp_path`.
static int	create_pathname(t_string *pathname, t_string *exec, char *envp_path)
{
	int	path_len;
	int	add_slash;

	path_len = 0;
	while (envp_path[path_len] && envp_path[path_len] != ':')
		path_len++;
	add_slash = (path_len != 0 && envp_path[path_len - 1] != '/');
	if (path_len + add_slash + exec->size > pathname->size)
	{
		free(pathname->ptr);
		pathname->ptr = malloc((path_len + add_slash + exec->size)
				* sizeof (char));
		if (!pathname->ptr)
		{
			perror("malloc");
			return (-1);
		}
		pathname->size = path_len + add_slash + exec->size;
	}
	ft_strlcpy(pathname->ptr, envp_path, path_len + 1);
	if (add_slash)
		pathname->ptr[path_len] = '/';
	ft_strlcpy(pathname->ptr + path_len + add_slash, exec->ptr, exec->size);
	return (path_len);
}

/// @brief Creates two `t_string`'s for `find_pathname()`.
/// @param pathname A duplicate of `exec_name`,
// 		an empty `string` if `exec_name` is `NULL`.
/// @param exec A `t_string` pointing to `exec_name` and storing its size.
/// @return `0` if success, `-1` if an error occured.
static int	init_pathname(t_string *pathname, t_string *exec, char *exec_name)
{
	*exec = create_t_string(exec_name);
	if (exec->size == -1)
		pathname->ptr = ft_strdup("");
	else
		pathname->ptr = ft_strdup(exec_name);
	if (!pathname->ptr)
		return (-1);
	*pathname = create_t_string(pathname->ptr);
	return (0);
}

/// @brief Looks through `envp_path` to find a valid `pathname`
// 		that can be executed.
/// @param exec Name of the executable to find.
/// @return `1` if found, `0` if not, `-1` if an error occured.
static int	look_through_envlst(t_string *pathname, t_string *exec,
	char *envp_path)
{
	int			jump;

	while (*envp_path)
	{
		if (access(pathname->ptr, X_OK) == 0)
			return (1);
		while (*envp_path && *envp_path == ':')
			envp_path++;
		jump = create_pathname(pathname, exec, envp_path);
		if (jump == -1)
			return (-1);
		envp_path += jump;
	}
	return (0);
}

char	*find_pathname(char *exec_name, char *envp_path)
{
	t_string	pathname;
	t_string	exec;
	int			init;
	int			found;

	init = init_pathname(&pathname, &exec, exec_name);
	if (init == -1)
		return (NULL);
	if (pathname.ptr[0] == '\0' || access(pathname.ptr, X_OK) == 0)
		return (pathname.ptr);
	if (!envp_path)
	{
		pathname.ptr[0] = '\0';
		return (pathname.ptr);
	}
	found = look_through_envp(&pathname, &exec, envp_path);
	if (found == -1)
		return (NULL);
	else if (found == 0)
		pathname.ptr[0] = '\0';
	return (pathname.ptr);
}
