/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:38:45 by egomez            #+#    #+#             */
/*   Updated: 2024/07/19 11:54:55 by maamine          ###   ########.fr       */
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

static int	error(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (is_delimiter(arg[i]))
		{
			if (arg[i] != '+')
				return (1);
		}
		i++;
	}
	return (0);
}

static	int	handle_args(char *content, t_env **envi)
{
	int	i;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	if (content[i] != '=')
	{
		i = 0;
		while (content[i] && !is_delimiter(content[i]))
			i++;
		if (content[i] && is_delimiter(content[i]))
		{
			error_message(content);
			return (1);
		}
		set_null(envi, content);
	}
	else if (content[i - 1] == '+')
		return (export_join(envi, content));
	else
	{
		if (check_arg(content))
			return (1);
		else
			return (export_update(envi, content));
	}
	return (0);
}

int	export_add(t_env **envi, t_list *args)
{
	int	exit_s;

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
		exit_s = (handle_args(args->content, envi) || exit_s);
		args = args->next;
	}
	return (exit_s);
}
