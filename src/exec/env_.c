/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:21:11 by maamine           #+#    #+#             */
/*   Updated: 2024/06/24 15:48:06 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static size_t	env_size(t_env *env)
// {
// 	size_t	size;
// 
// 	size = 0;
// 	while (env)
// 	{
// 		env = env->next;
// 		size++;
// 	}
// 	return (size);
// }

static char	*env_to_str(t_env *env)
{
	char	*str;
	size_t	key_len;
	size_t	val_len;

	key_len = ft_strlen(env->name);
	if (env->val)
		val_len = ft_strlen(env->val);
	else
		val_len = 0;
	str = malloc((key_len + val_len + 2) * sizeof (char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, env->name, key_len + 1);
	str[key_len] = '=';
	ft_strlcpy(str + key_len + 1, env->val, val_len + 1);
	return (str);
}

static void	free_achar(char **achar)
{
	int	i;

	i = 0;
	while (achar[i])
	{
		free(achar[i]);
		i++;
	}
	free(achar);
}

char	**envlst_to_envp(t_env *env)
{
	char	**envp;
	size_t	size;
	size_t	i;

	size = env_size(env);
	envp = malloc((size + 1) * sizeof (char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		envp[i] = env_to_str(env);
		if (!envp[i])
		{
			free_achar(envp);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	return (envp);
}
