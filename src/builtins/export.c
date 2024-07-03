/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:36:25 by maamine           #+#    #+#             */
/*   Updated: 2024/06/26 19:18:44 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	convert_in_tab(t_env *envi, char **new_env)
{
	int	i;

	i = 0;
	while (envi)
	{
		if (ft_strcmp(envi->name, "_"))
		{
			new_env[i] = ft_strdup(envi->name);
			if (envi->val)
			{
				new_env[i] = ft_strjoin_char(new_env[i], '=', true);
				new_env[i] = ft_strjoin(new_env[i], envi->val);
			}
			i++;
		}
		envi = envi->next;
	}
}

static void	bubble_sort(char **new_env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (new_env[i])
	{
		if (new_env[i + 1])
		{
			if (ft_strcmp(new_env[i], new_env[i + 1]) > 0)
			{
				tmp = new_env[i];
				new_env[i] = new_env[i + 1];
				new_env[i + 1] = tmp;
				i = 0;
			}
			else
				i++;
		}
		else
			i++;
	}
}

static void	free_env(char **new_env)
{
	int	i;

	i = 0;
	while (new_env[i])
	{
		free(new_env[i]);
		i++;
	}
	free(new_env);
}

static void	print_export(t_env *envi, char **new_env)
{
	int		i;
	int		y;
	char	**to_print;
	t_env	*current;

	i = 0;
	current = envi;
	while (new_env[i])
	{
		y = 0;
		current = envi;
		while (new_env[i][y] != 0 && new_env[i][y] != '=')
			y++;
		if (new_env[i][y] != '=')
		{
			while (current && ft_strcmp(current->name, new_env[i]))
				current = current->next;
			if (current->init == false)
				printf("declare -x %s\n", new_env[i]);
			else
				printf("declare -x %s=\"\"\n", new_env[i]);
		}
		else
		{
			to_print = sep_on_equal(new_env[i]);
			printf("declare -x %s=\"%s\"\n", to_print[0], to_print[1]);
			free_split(to_print);
		}
		// printf("%d\n", i);
		// if (i == 37)
		// 	printf("breakpoint here\n");
		i++;
	}
}

int	export(t_env *envi)
{
	char	**new_env;

	if (envi == NULL)
		return (0);
	new_env = ft_calloc(env_size(envi) + 1, sizeof (char *));
	convert_in_tab(envi, new_env);
	bubble_sort(new_env);
	print_export(envi, new_env);
	free_env(new_env);
	return (0);
}
