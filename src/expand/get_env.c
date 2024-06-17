/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:39:20 by egomez            #+#    #+#             */
/*   Updated: 2024/04/29 16:39:29 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env   *get_env(char **env_var)
{
    int     i;
    int     secure;
    t_env   *env_lst;
    char    **current_var;

    i = 0;
    env_lst = NULL;
    while (env_var[i] != 0)
    {
        secure = 0;
        current_var = ft_split(env_var[i], '=');
        while (current_var[secure])
            secure++;
        if (secure > 1)
            env_add_back(&env_lst, env_new(ft_strdup(current_var[0]), ft_strdup(current_var[1])));
        i++;
        free_split(current_var);
    }
    return (env_lst);
}