/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:32:02 by maamine           #+#    #+#             */
/*   Updated: 2024/06/06 15:45:24 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**arglst_to_argv(t_list *arguments)
{
	char	**argv;
	int		size;
	int		i;

	size = ft_lstsize(arguments);
	argv = malloc((size + 1) * sizeof (char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < size)
	{
		argv[i] = arguments->content;
		arguments = arguments->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

t_attributes	fill_attributes(t_exec *exec, char **envp)
{
	t_attributes	attributes;

	attributes.envp = envp;
	if (!attributes.envp)
	{
		attributes.argv = NULL;
		attributes.pathname = NULL;
		return (attributes);
	}
	attributes.argv = arglst_to_argv(exec->cmd->arguments);
	if (!attributes.argv)
	{
		free_achar(&attributes.envp);
		attributes.pathname = NULL;
		return (attributes);
	}
	attributes.pathname = find_pathname(attributes.argv, envp);
	if (!attributes.pathname)
	{
		free_achar(&attributes.envp);
		free(attributes.argv);
	}
	return (attributes);
}
