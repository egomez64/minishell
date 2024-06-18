/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:21:11 by maamine           #+#    #+#             */
/*   Updated: 2024/06/18 20:03:49 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*env_to_str(t_env *env)
{
	char	*str;
	size_t	key_len;
	size_t	val_len;

	key_len = ft_strlen(env->name);
	val_len = ft_strlen(env->val);
	str = malloc((key_len + val_len + 2) * sizeof (char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, env->name, key_len + 1);
	str[key_len] = '=';
	ft_strlcpy(str + key_len + 1, env->val, key_len + val_len + 2);
	str[key_len + val_len + 1] = '\0';
	return (str);
}

char	**envlst_to_envp(t_env *env)
{
	char	**envp;
	t_env	*current;
	size_t	size;
	size_t	i;

	current = env;
	size = 1;
	while (current)
	{
		current = current->next;
		size++;
	}
	envp = malloc(size * sizeof (char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		envp[i] = env_to_str(env);
		if (!envp[i])
		{
			// free_achar(envp);
			return (NULL);
		}
		i++;
	}
	return (envp);
}
