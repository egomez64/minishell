/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamine <maamine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:21:11 by maamine           #+#    #+#             */
/*   Updated: 2024/07/20 17:24:05 by maamine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*find_in_env(t_env *envi, char *val_name)
{
	while (envi && ft_strcmp(envi->name, val_name))
		envi = envi->next;
	return (envi);
}

static char	*env_to_str(t_env **env)
{
	char	*str;
	size_t	key_len;
	size_t	val_len;

	key_len = ft_strlen((*env)->name);
	if ((*env)->val)
		val_len = ft_strlen((*env)->val);
	else
		val_len = 0;
	str = malloc((key_len + val_len + 2) * sizeof (char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (*env)->name, key_len + 1);
	str[key_len] = '=';
	if ((*env)->val)
		ft_strlcpy(str + key_len + 1, (*env)->val, val_len + 1);
	return (str);
}

char	**envlst_to_envp(t_env **env)
{
	char	**envp;
	size_t	size;
	size_t	i;

	size = env_size(*env);
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
		env = &(*env)->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
