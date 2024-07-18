/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:38:45 by egomez            #+#    #+#             */
/*   Updated: 2024/07/04 17:51:59 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	error_message(char *arg)
{
	char	*str;
	int		arg_len;

	arg_len = ft_strlen(arg);
	str = malloc((47 + arg_len) * sizeof (char));
	if (!str)
		return ;
	ft_strlcpy(str, "minishell: export: `", 21);
	ft_strlcpy(str + 20, arg, arg_len + 1);
	ft_strlcpy(str + 20 + arg_len, "\': not a valid identifier\n", 27);
	write(2, str, ft_strlen(str));
	free(str);
}

static int	check_arg(char *s)
{
	int	i;

	i = 0;
	if (s[0] >= '0' && s[0] <= '9')
		return (1);
	while (s[i] && s[i] != '=')
	{
		if (is_delimiter(s[i]))
			return (1);
		i++;
	}
	if (!s[i])
		return (1);
	return (0);
}

static int	export_join(t_env **envi, char *s)
{
	char	**new;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = *envi;
	new = sep_on_equal(s);
	while (new[0][i] != '+')
		i++;
	new[0][i] = 0;
	while (tmp && ft_strcmp(tmp->name, new[0]))
		tmp = tmp->next;
	if (tmp)
	{
		tmp->val = ft_strjoin(tmp->val, new[1]);
		free(new[0]);
		free(new);
	}
	else
	{
		free(new);
		return (1);
	}
	return (0);
}

static int	export_append(t_env **envi, char *s)
{
	char	**new_var;
	t_env	*first;

	first = *envi;
	new_var = sep_on_equal(s);
	while (first && ft_strcmp(first->name, new_var[0]))
		first = first->next;
	if (first)
		first->val = new_var[1];
	else
	{
		env_add_back(envi, env_new(new_var[0], new_var[1], true));
		free(new_var);
	}
	return (0);
}

static int	set_null(t_env **envi, char *s)
{
	t_env	*current;
	bool	equal;

	current = *envi;
	equal = (s[ft_strlen(s) - 1] == '=');
	if (equal)
		s[ft_strlen(s) - 1] = 0;
	while (current && ft_strcmp(current->name, s))
		current = current->next;
	if (current)
	{
		current->val = NULL;
		if (equal)
			current->init = equal;
	}
	else
		env_add_back(envi, env_new(s, NULL, equal));
	return (0);
}

static int	error(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]))
		return (1);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (is_delimiter(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	export_add(t_env **envi, t_list *args)
{
	int	i;
	int	exit_s;

	i = 0;
	exit_s = 0;
	if (envi == NULL)
		return (0);
	args = args->next;
	while (args)
	{
		if (args->content[0] == '_'
			&& (!args->content[1] || args->content[1] == '='))
		{
			args = args->next;
			continue ;
		}
		if (error(args->content))
		{
			error_message(args->content);
			args = args->next;
			exit_s = 1;
			continue ;
		}
		while (args->content[i] && args->content[i] != '=')
			i++;
		if (args->content[ft_strlen(args->content) - 1] == '='
			|| args->content[i] != '=')
			set_null(envi, args->content);
		else if (args->content[i - 1] == '+')
			exit_s = (exit_s || export_join(envi, args->content));
		else
		{
			if (check_arg(args->content))
				exit_s = 1;
			else
				exit_s = (exit_s || export_append(envi, args->content));
		}
		args = args->next;
	}
	return (exit_s);
}
