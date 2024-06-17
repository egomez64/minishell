/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:32:02 by maamine           #+#    #+#             */
/*   Updated: 2024/06/17 15:23:16 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_achar(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**arglst_to_argv(t_list *arguments)
{
	char	**argv;
	int		size;
	int		i;

	size = ft_lstsize(arguments);
	dprintf(3, "size: %d\n", size);
	argv = malloc((size + 1) * sizeof (char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dprintf(3, "\t%s\n", (char *) arguments->content);
		argv[i] = arguments->content;
		arguments = arguments->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

/// @brief Looks through environment variables
// 		for the contents of the `var` key.
/// @param envp Environment variables.
/// @param var Key.
/// @return Contents of `var` in `envp`.
static char	*envp_find(char *envp[], char *var)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (var[j] && var[j] == envp[i][j])
			j++;
		if (var[j] == '\0' && envp[i][j] == '=')
			return (envp[i] + j + 1);
		i++;
	}
	return (NULL);
}

void	free_attributes(t_attributes attributes)
{
	free(attributes.pathname);
	free_achar(attributes.argv);
	free_achar(attributes.envp);
}

t_attributes	fill_attributes(t_exec *exec, t_env *env, char **envp)
{
	t_attributes	attributes;
	char			*envp_path;

	(void) env;
	attributes.envp = envp;
	if (!attributes.envp)
	{
		attributes.argv = NULL;
		attributes.pathname = NULL;
		return (attributes);
	}
	dprintf(3, "%d argv:\n", getpid());
	attributes.argv = arglst_to_argv(exec->cmd->arguments);
	if (!attributes.argv)
	{
		free_achar(attributes.envp);
		attributes.pathname = NULL;
		return (attributes);
	}
	envp_path = envp_find(envp, "PATH");
	attributes.pathname = find_pathname(attributes.argv[0], envp_path);
	if (!attributes.pathname)
	{
		free_achar(attributes.envp);
		free(attributes.argv);
	}
	dprintf(3, "%d pathname: %s\n", getpid(), attributes.pathname);
	return (attributes);
}
