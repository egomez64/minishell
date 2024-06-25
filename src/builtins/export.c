/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:36:25 by maamine           #+#    #+#             */
/*   Updated: 2024/06/24 17:35:38 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	convert_in_tab(t_env *envi, char **new_env)
{
	int	i;

	i = 0;
	while (envi)
	{
		new_env[i] = ft_strdup(envi->name);
		if (envi->val)
		{
			new_env[i] = ft_strjoin_char(new_env[i], '=', true);
			new_env[i] = ft_strjoin(new_env[i], envi->val);
		}
		i++;
		envi = envi->next;
	}
}

void	bubble_sort(char **new_env)
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

void	free_env(char **new_env)
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

void	print_export(t_env **envi, char **new_env)
{
	int		i;
	int		y;
	char	**to_print;
	t_env	*first;

	i = 0;
	while (new_env[i])
	{
		first = *envi;
		y = 0;
		while (new_env[i][y] != 0 && new_env[i][y] != '=')
			y++;
		if (new_env[i][y] != '=')
		{
			while (first && ft_strcmp(first->name, new_env[i]))
				first = first->next;
			if (first->init == false)
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
		i++;
	}
}

int	export(t_env *envi)
{
	char	**new_env;

	new_env = ft_calloc(env_size(envi) + 1, sizeof (char *));
	convert_in_tab(envi, new_env);
	bubble_sort(new_env);
	print_export(&envi, new_env);
	free_env(new_env);
	return (0);
}
