/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:36:25 by maamine           #+#    #+#             */
/*   Updated: 2024/07/18 10:03:10 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*env_to_str(t_env *env_var)
{
	char	*str;
	int		name_len;
	int		val_len;

	name_len = ft_strlen(env_var->name);
	if (env_var->init)
		val_len = ft_strlen(env_var->val);
	else
		val_len = -3;
	str = malloc((12 + name_len + 2 + val_len + 1 + 1) * sizeof (char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, "declare -x ", 12);
	ft_strlcpy(str + 11, env_var->name, name_len + 1);
	if (val_len != -3)
	{
		ft_strlcpy(str + 11 + name_len, "=\"", 3);
		ft_strlcpy(str + 11 + name_len + 2, env_var->val, val_len + 1);
		ft_strlcpy(str + 11 + name_len + 2 + val_len, "\"", 2);
	}
	return (str);
}

static void	convert_in_tab(t_env *envi, char **new_env)
{
	int	i;

	i = 0;
	while (envi)
	{
		if (ft_strcmp(envi->name, "_"))
		{
			new_env[i] = env_to_str(envi);
			i++;
		}
		envi = envi->next;
	}
}

// static void	convert_in_tab(t_env *envi, char **new_env)
// {
// 	int	i;
// 
// 	i = 0;
// 	while (envi)
// 	{
// 		if (ft_strcmp(envi->name, "_"))
// 		{
// 			new_env[i] = ft_strdup(envi->name);
// 			if (envi->val)
// 			{
// 				new_env[i] = ft_strjoin_char(new_env[i], '=', true);
// 				new_env[i] = ft_strjoin(new_env[i], envi->val);
// 			}
// 			i++;
// 		}
// 		envi = envi->next;
// 	}
// }

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

static void	print_export(char **new_env)
{
	int		i;

	i = 0;
	while (new_env[i])
	{
		printf("%s\n", new_env[i]);
		i++;
	}
}

// static void	print_export(t_env *envi, char **new_env)
// {
// 	int		i;
// 	int		y;
// 	char	**to_print;
// 	t_env	*current;
// 
// 	i = 0;
// 	current = envi;
// 	while (new_env[i])
// 	{
// 		y = 0;
// 		current = envi;
// 		while (new_env[i][y] != 0 && new_env[i][y] != '=')
// 			y++;
// 		if (new_env[i][y] != '=')
// 		{
// 			while (current && ft_strcmp(current->name, new_env[i]))
// 				current = current->next;
// 			if (current->init == false)
// 				printf("declare -x %s\n", new_env[i]);
// 			else
// 				printf("declare -x %s=\"\"\n", new_env[i]);
// 		}
// 		else
// 		{
// 			to_print = sep_on_equal(new_env[i]);
// 			printf("declare -x %s=\"%s\"\n", to_print[0], to_print[1]);
// 			free_split(to_print);
// 		}
// 		i++;
// 	}
// }

int	export(t_env *envi)
{
	char	**new_env;

	if (envi == NULL)
		return (0);
	new_env = ft_calloc(env_size(envi) + 1, sizeof (char *));
	convert_in_tab(envi, new_env);
	bubble_sort(new_env);
	print_export(new_env);
	free_achar(new_env);
	return (0);
}
