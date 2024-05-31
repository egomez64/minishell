/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:08:57 by egomez            #+#    #+#             */
/*   Updated: 2024/04/30 15:09:01 by egomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_var(t_cmd **commands, t_env **env_var)
{
    t_cmd   *tmp_cmd;
    t_list  *tmp_arg;
    t_token *tmp_red;

    tmp_cmd = *commands;
    while(tmp_cmd)
    {
        tmp_arg = tmp_cmd->arguments;
        tmp_red = tmp_cmd->redirections;
        while(tmp_arg)
        {
            tmp_arg->content = handle_var(tmp_arg->content, *env_var);
            tmp_arg = tmp_arg->next;
        }
        while(tmp_red)
        {
            tmp_red->val = handle_var(tmp_red->val, *env_var);
            tmp_red = tmp_red->next;
        }
        tmp_cmd = tmp_cmd->next;
    }
}