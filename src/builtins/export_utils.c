/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:27:49 by egomez            #+#    #+#             */
/*   Updated: 2024/06/26 19:16:14 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**sep_on_equal(char *s)
{
	char	**new;
	int		i;
	int		y;

	i = 0;
	y = 0;
	new = ft_calloc(3, sizeof(char *));
	while (s[i] && s[i] != '=')
		i++;
	new[0] = ft_substr(s, 0, i);
	i++;
	y = i;
	while (s[i])
		i++;
	new[1] = ft_substr(s, y, i - y);
	return (new);
}

static void	handle_new_env_var(t_env **new_env_var, char **new)
{
	char	*tmp_val;

	if (!(*new_env_var)->val)
		(*new_env_var)->val = new[1];
	else
	{
		tmp_val = (*new_env_var)->val;
		(*new_env_var)->val = ft_strjoin(tmp_val, new[1]);
		free(tmp_val);
		free(new[1]);
	}
	free(new[0]);
}

int	export_join(t_env **envi, char *s)
{
	char	**new;
	int		i;
	t_env	*new_env_var;

	i = 0;
	new_env_var = *envi;
	new = sep_on_equal(s);
	while (new[0][i] != '+')
		i++;
	new[0][i] = 0;
	while (new_env_var && ft_strcmp(new_env_var->name, new[0]))
		new_env_var = new_env_var->next;
	if (new_env_var)
		handle_new_env_var(&new_env_var, new);
	else
		env_add_back(envi, env_new(new[0], new[1]));
	free(new);
	return (0);
}

int	set_null(t_env **envi, char *s)
{
	t_env	*current;
	char	*dup;

	current = *envi;
	while (current && ft_strcmp(current->name, s))
		current = current->next;
	if (current && ft_strcmp(current->name, s) == 0)
		return (0);
	dup = ft_strdup(s);
	env_add_back(envi, env_new(dup, NULL));
	return (0);
}

int	export_update(t_env **envi, char *s)
{
	char	**new_var;
	t_env	*first;

	first = *envi;
	new_var = sep_on_equal(s);
	while (first && ft_strcmp(first->name, new_var[0]))
		first = first->next;
	if (first)
	{
		free(first->val);
		first->val = new_var[1];
		free(new_var[0]);
		free(new_var);
	}
	else
	{
		env_add_back(envi, env_new(new_var[0], new_var[1]));
		free(new_var);
	}
	return (0);
}
